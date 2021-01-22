#include "assembler.h"

int assembler (FILE *file_path){
    /* declaring data types */
    TableRow *command_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    TableRow *directive_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    /* OperationItem operation_table[OPT_SIZE] = get_operation_table(); */
    OperationItem *operation_table = (OperationItem *)malloc(OPT_SIZE * sizeof(OperationItem));
    SymbolNode *root = get_symbol_root();

    int IC = 100;
    int DC = 0;
    int L = 0;
    char line[80];
    char *label;
    int directive=data;
    char *argument;
    OperationItem command;

    /* temp vars - to make assignments */
    char *temp_s1;
    char *temp_s2;
    char temp_c;
    int temp_i;
    int source;
    int label;
    word *w1, *w2;

    int is_label = FALSE; /* flag weather the next line has a label */
    int is_direct = FALSE; /* flag weather the next line is a directive line */

    operation_table = get_operation_table();

    while (strcmp(line, "\0") != 0){
        /* (line = get_line(file_path)) != '\0' */
        argument = get_first_token(line);
        label = get_label(argument);
        if (strcmp(label, "\0") != 0){
            is_label = TRUE;
            argument = get_next_token();
            if ((directive = is_directive(argument)) != -1){
                is_direct = TRUE;
            }
        }
        else if ((directive = is_directive(argument)) != -1){
            is_direct = TRUE;
        }


        if (is_direct==TRUE){
            /* THIS LINE IS A DIRECT LINE */
            if (is_label==TRUE && (directive==data || directive==string)){
                /* deal with attributes array [2] later */
                /* add the line to the symbol table */
                add_symbol_node(label, DC, data, get_last_node(root));
                /* add the command to the data table */

                /* evaluate for cases - if string add each char in different word and finish with \0
                * if str just put the numbers until there is no more numbers */
                if (directive == data){
                    while ((temp_s1=get_next_token()) != NULL){
                        drop_comma(temp_s1);
                        if (atoi(temp_s1) == 0 && !isdigit(*temp_s1)) {
                            /* PRINT ERROR MESSAGE ?? */
                            continue;
                        }
                        temp_i = atoi(temp_s1);
                        directive_memory[DC].w = *get_word(temp_i);
                        DC++;
                    }
                }
                else {
                    temp_s1 = get_next_token();
                    drop_marks(temp_s1);
                    for (temp_i = 0;  temp_s1[temp_i] != '\0' ; temp_i++) {
                        directive_memory[DC].w = *get_word(temp_s1[temp_i]);
                        DC++;
                    }
                    directive_memory[DC].w = *get_word('\0');
                    DC++;
                }
            }
            else if (directive==external){
                add_symbol_node(label, 0, external, get_last_node(root));
            }
            else {
                /* intern - we dont deal with that in the first round */
            }

        }
        else{
            /* THIS LINE IS A INSTRUCTION LINE */
            if (is_label==TRUE){
                /* ADD TO THE SYMBOL TABLE */
                add_symbol_node(label, IC, code, get_last_node(root));
            }
            /* search the operation name (mov, add) int the table */
            command = get_command(get_next_token(), operation_table);
            L = command.words_num;
            if (L == 2){
                argument = get_next_token();
                if (is_comma(argument)){
                    temp_s1 = get_first_operand(argument);
                    temp_s2 = get_second_operand();
                }
                else{
                    temp_s1 = get_next_token();
                    if (is_comma(temp_s1)){
                        drop_comma(temp_s1);
                        temp_s2 = get_next_token();
                    }
                    else{
                        temp_s2 = get_next_token();
                        if(*temp_s2 == ',' && *(temp_s2+1) == '\0'){
                            temp_s2 = get_next_token();
                        }
                        else if (is_comma(temp_s2)){
                            drop_comma(temp_s2);
                        }
                        else{
                            /* print error - no comma */
                        }
                    }
                }
                source = operand_address_method(temp_s1);
                dest = operand_address_method(temp_s2);
                command_memory[IC++] = get_first_word(command, source, dest);
                /* add the words depends on the address method */
                switch (source) {
                    case 0:
                        w1 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w1 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w1 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w1 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w1;
                switch (dest) {
                    case 0:
                        w2 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w2 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w2 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w2 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w2;
            }
            else if (L == 1){
                temp_s1 = get_next_token();
                dest = operand_address_method(temp_s2);
                command_memory[IC] = get_first_word(command, 0, dest);
                /* add the words depends on the address method */
                switch (dest) {
                    case 0:
                        w1 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w1 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w1 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w1 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w1;
            }
            else{
                command_memory[IC++] = get_first_word(command, 0, 0);
            }








        }

        /* reset the variabels */

        strcpy(line, get_line(file_path));









    }


    return 1;
}

