#include "second_stage.h"
#include "constants.h"
#include "text_process.h"
#include "data_structures.h"
#include "assembler_main.h"
#include "debug_tools.h"
#include <stdlib.h>
#include <string.h>
char *word_to_hexa(word *w);

OperationL L_table [] ={
        {"mov", 2},
        {"cmp", 2},
        {"add", 2},
        {"sub", 2},
        {"lea", 2},
        {"clr", 1},
        {"not", 1},
        {"inc", 1},
        {"dec", 1},
        {"jmp", 1},
        {"bne", 1},
        {"jsr", 1},
        {"red", 1},
        {"prn", 1},
        {"rts", 0},
        {"stop", 0},
        {"null", 0}
};

int IS_ENTRY = FALSE, IS_EXTERNAL = FALSE, ERROR = FALSE;

int second_stage(FILE *file, char *file_name){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    char source_label[MAX_LABEL];
    char dest_label[MAX_LABEL];
    int source_adress;
    int dest_adress;
    int directive_type = data;
    int ic_pointer, L;
    enum boolean IS_DIRECT = FALSE; /*IS_LABEL = FALSE */
    int EXT_VAR = FALSE;
    OperationL *command;

    ic_pointer = 100;
    L = 0;
    while (!feof(file))
    {
        get_line(file, line);

        if (!is_comment_line(line) && !is_empty_line(line)){
            get_first_token(line, argument);
            if (get_label(line, label, &ERROR, UNKNOWN_LINE)==1){
                /*IS_LABEL = TRUE; commented to silence unused warning */
                get_next_token(argument);
                if ((directive_type = is_directive(argument)) != -1){
                    IS_DIRECT = TRUE;
                }
            }
            else if ((directive_type = is_directive(argument)) != -1){
                IS_DIRECT = TRUE;
            }
        }
        if ( directive_type == entry){
            get_next_token(argument);
            /* search the label in the symbol list */
            if(add_entry_to_symbol(argument)==0){
                /* print error */
            }
            IS_ENTRY = TRUE;
        }
        if(IS_DIRECT == FALSE){
            get_command_L(argument, &command, L_table);
            L = command->words_num;
            ic_pointer++;
            switch (L){
            /* AMIT - source_adress, dest_adress CONTAIN 1 FOR DIRECT OR 2 FOR RELATIVE, UNINITIALIZED ELSE.
            IF THERE IS LABEL IN THE OPERANDS - source_label, dest_label CONTAIN IT, UNINITIALIZED ELSE. */
            case 2:
                /*we know that DIRECT is optional (1) search in dest or source */
                /*check the first operand*/
                get_next_token(argument);
                drop_comma(argument);
                source_adress =  operand_address_method(argument);
                if(source_adress == 1){
                    strcpy(source_label, argument);
                    command_memory[ic_pointer].w = get_word_direct(source_label, root, &ERROR, &EXT_VAR);
                    switch (EXT_VAR)
                    {
                    case FALSE:
                        command_memory[ic_pointer].ARE = R;
                        break;
                    case TRUE:
                        command_memory[ic_pointer].ARE = E;
                        IS_EXTERNAL = TRUE;
                        add_external_list_node(source_label, ic_pointer, get_last_external_list_node(external_list_root));
                        break;
                    }
                }   
                ic_pointer++;    
                /*check the second operand*/
                get_next_token(argument);
                dest_adress =  operand_address_method(argument);
                if(dest_adress == 1){
                    strcpy(dest_label, argument);
                    command_memory[ic_pointer].w = get_word_direct(dest_label, root, &ERROR, &EXT_VAR);
                    switch (EXT_VAR)
                    {
                    case FALSE:
                        command_memory[ic_pointer].ARE = R;
                        break;
                    case TRUE:
                        command_memory[ic_pointer].ARE = E;
                        IS_EXTERNAL = TRUE;
                        add_external_list_node(dest_label, ic_pointer, get_last_external_list_node(external_list_root));
                        break;
                    }
                }

                ic_pointer++;
                break;
            
            case 1:
                /* we know that DIRECT and RELATIVE (1,2) is optional search in dest */
                get_next_token(argument);
                dest_adress =  operand_address_method(argument);
                if(dest_adress == 1){
                    strcpy(dest_label, argument);
                    command_memory[ic_pointer].w = get_word_direct(dest_label, root, &ERROR, &EXT_VAR);
                    switch (EXT_VAR)
                    {
                    case FALSE:
                        command_memory[ic_pointer].ARE = R;
                        break;
                    case TRUE:
                        command_memory[ic_pointer].ARE = E;
                        IS_EXTERNAL = TRUE;
                        add_external_list_node(dest_label, ic_pointer, get_last_external_list_node(external_list_root));
                        break;
                    }
                }
                if(dest_adress == 2){ /*we dont need the - % */
                    strcpy(dest_label, &argument[1]);
                    command_memory[ic_pointer].w = get_word_relative(dest_label, ic_pointer, root, &EXT_VAR, &ERROR);
                    switch (EXT_VAR)
                    {
                    case FALSE:
                        command_memory[ic_pointer].ARE = R;
                        break;
                    case TRUE:
                        command_memory[ic_pointer].ARE = E;
                        IS_EXTERNAL = TRUE;
                        add_external_list_node(dest_label, ic_pointer, get_last_external_list_node(external_list_root));
                        break;
                    }
                }
                ic_pointer++;
                break;

            case 0:
                break;
            }
        }
        /* reset variabels */
        EXT_VAR = FALSE;
        IS_DIRECT = FALSE;
    }

    if (ERROR == FALSE)
    {
        create_files(file_name);
        return 1;

    }
    return 0;
}

void create_files(char *file_name){
    FILE *file_ob;
    int counter;
    TableRow *row;
    char *file_name_ob = (char *)malloc(sizeof(char)*MAX_LABEL);;
    

if(IS_ENTRY == TRUE){
        create_entry(file_name);
    }
    if(IS_EXTERNAL == TRUE){
        create_external(file_name);
    }

    /* create .ob*/
    
    strcpy(file_name_ob, file_name);
    strcat(file_name_ob, ".ob");

    file_ob = fopen(file_name_ob, "w");
    counter = 100;

    fprintf(file_ob, "\t%d %d\n", IC-100, DC);
    while (counter<IC+DC)
    {
        row = &command_memory[counter];
        fprintf(file_ob, "%d %03x ", counter, row->w->bits);
        switch (row->ARE)
        {
        case 0:
            fprintf(file_ob, "A\n");
            break;
        case 1:
            fprintf(file_ob, "R\n");
            break;
        case 2:
            fprintf(file_ob, "E\n");
            break;
        }
        counter++;
    }
    fclose(file_ob);
    free(file_name_ob);
}

void create_entry(char *file_name){
    FILE *file_ent;
    char *file_name_ent = (char *)malloc(sizeof(char)*MAX_LABEL);
    SymbolNode *node = root;

    strcpy(file_name_ent, file_name);
    strcat(file_name_ent, ".ent");
    file_ent = fopen(file_name_ent, "w");

    while(node->next != NULL){
        node = node->next;
        if (node->attribute & 2){
            fprintf(file_ent, "%s %04d\n", node->symbol, node->value);
        }
    }
    fclose(file_ent);
    free(file_name_ent);
}

void create_external(char *file_name){
    FILE *file_ext;
    char *file_name_ext = (char *)malloc(sizeof(char)*MAX_LABEL);
    External_list_Node *node = external_list_root;

    strcpy(file_name_ext, file_name);
    strcat(file_name_ext, ".ext");
    file_ext = fopen(file_name_ext, "w");

    while(node->next != NULL){
        node = node->next;
        fprintf(file_ext, "%s %04d\n", node->symbol, node->value);
    }
    fclose(file_ext);
    free(file_name_ext);
}
