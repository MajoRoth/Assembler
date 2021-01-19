#include "assembler.h"

int assembler (FILE *file_path){
    /* declaring data types */
    TableRow command_memory[MAX_TABLE];
    TableRow directive_memory[MAX_TABLE];
    OperationItem operation_table[OPT_SIZE] = get_operation_table();
    SymbolNode *root = get_symbol_root();

    int IC = 100;
    int DC = 0;
    int L = 0;
    char line[80];
    char *label;
    int directive=data;
    char *argument;
    OperationItem command;

    char *temp_s;
    char temp_c;
    int temp_i;

    int is_label = FALSE; /* flag weather the next line has a label */
    int is_direct = FALSE; /* flag weather the next line is a directive line */
    int attributes[2];

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
                    while ((temp_s=get_next_token()) != NULL){
                        drop_comma(temp_s);
                        if (atoi(temp_s) == 0 && !isdigit(*temp_s)) {
                            /* PRINT ERROR MESSAGE ?? */
                            continue;
                        }
                        temp_i = atoi(temp_s);
                        directive_memory[DC].w = *get_word(temp_i);
                        DC++;
                    }
                }
                else {
                    temp_s = get_next_token();
                    drop_marks(temp_s);
                    for (temp_i = 0;  temp_s[temp_i] != '\0' ; temp_i++) {
                        directive_memory[DC].w = *get_word(temp_s[temp_i]);
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
            /*
             * word = get_first_word();
             * command_array[IC] = word;
             * IC++
             * word = get_next()
             * command_array[IC] = word;
             * IC++
             */

            /* generate the code and add it to the ram */
            IC += L;
        }

        /* reset the variabels */
        L=0;

        strcpy(line, get_line(file_path));









    }



}

