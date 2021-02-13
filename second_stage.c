#include "second_stage.h"
#include "constants.h"
#include "text_process.h"
#include "data_structures.h"
#include "assembler_main.h"
#include <stdlib.h>
#include <string.h>

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


int second_stage(FILE *file){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    char source_label[MAX_LABEL];
    char dest_label[MAX_LABEL];
    int source_adress;
    int dest_adress;
    int directive_type = data;
    int ic_pointer, L, i;
    enum boolean IS_LABEL = FALSE, IS_DIRECT = FALSE, CONTINUE = FALSE;
    OperationL *command;

    printf("SECOND STAGE STARTED\n");
    ic_pointer = 100;
    L = 0;
    while (!feof(file))
    {
        get_line(file, line);
        printf("[ ] - current line: %s\n", line);

        if (!is_comment_line(line) && !is_empty_line(line)){
            get_first_token(line, argument);
            if (get_label(line, label)==1){
                IS_LABEL = TRUE;
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
        }
        else if (directive_type == data || directive_type == string || directive_type == external)
        {
            CONTINUE = TRUE;
        }

        if(CONTINUE == FALSE){
            get_command_L(argument, &command, L_table);
            L = command->words_num;

            switch (L)
            /* AMIT - source_adress, dest_adress CONTAIN 1 FOR DIRECT OR 2 FOR RELATIVE, UNINITIALIZED ELSE.
            IF THERE IS LABEL IN THE OPERANDS - source_label, dest_label CONTAIN IT, UNINITIALIZED ELSE. */
            {
            case 2:
                /*we know that DIRECT is optional (1) search in dest or source */
                /*check the first operand*/
                get_next_token(argument);
                source_adress =  operand_address_method(argument);
                if(source_adress == 1){
                    strcpy(source_label, argument);
                }       
                /*check the second operand*/
                get_next_token(argument);
                dest_adress =  operand_address_method(argument);
                if(dest_adress == 1){
                    strcpy(dest_label, argument);
                }
                break;
            
            case 1:
                /* we know that DIRECT and RELATIVE (1,2) is optional search in dest */
                get_next_token(argument);
                dest_adress =  operand_address_method(argument);
                if(dest_adress == 1){
                    strcpy(dest_label, argument);
                }
                if(dest_adress == 2){ /*we dont need the - % */
                    strcpy(dest_label, &argument[1]);
                }
                break;

            case 0:
                break;
            }
            
        }

        /* AMIT - 6 */

        if ((i = get_source(command_memory[ic_pointer].w)) == 1 || i == 2){
            
        }
        if ((i = get_dest(command_memory[ic_pointer].w)) == 1 || i == 2){
            
        }

        
        
        
    }
    print_table_symbol(root);
    return 1;
}

