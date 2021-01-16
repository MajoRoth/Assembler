//
// Created by Amit Roth on 09/01/2021.
//
#include "assembler.h"

int assembler (FILE *file_path){
    /* declaring data types */
    TableRow command_memory[MAX_TABLE];
    TableRow directive_memory[MAX_TABLE];
    struct OperationItem hash_table[16] = get_operation_table();
    SymbolNode root = get_symbol_root();

    int IC = 100;
    int DC = 0;
    int L = 0;
    char line[80];
    char *label;
    int directive;
    char *argument;

    char *temp_s;
    char temp_c
    int temp_i;

    int is_label = FALSE; /* flag weather the next line has a label */
    int is_direct = FALSE; /* flag weather the next line is a directive line */
    int directive = data;
    int attributes[2];

    while ((line = get_line(file_path)) != '\0'){
        argument = get_first_token(line);
        if ((label = is_label(argument)) != '\0'){
            is_label = TRUE;
            argument = get_next_token();
            if ((directive = is_directive(argument)) != -1){
                is_direct = TRUE;
            }
        }
        else ((directive = is_directive(argument)) != -1){
            is_direct = TRUE;
        }


        if (is_direct==TRUE){
            /* THIS LINE IS A DIRECT LINE */
            if (is_label==TRUE && (directive==data || directive==string)){
                /* deal with attributes array [2] later */
                /* add the line to the symbol table */
                add_symbol_node(label, DC, "data", get_last_node(root));
                /* add the command to the data table */

                /* evaluate for cases - if string add each char in different word and finish with \0
                * if str just put the numbers until there is no more numbers */
                if (directive == data){
                    while ((c=get_next_token()) != NULL){
                        drop_comma(c);
                        if (atoi(c) == 0 && !isdigit(drop_comma(c))) {
                            /* PRINT ERROR MESSAGE ?? */
                            continue;
                        }
                        drop_comma(c);
                        temp_i = atoi(c);
                        directive_memory[DC].w = get_word(temp_i);
                        DC++;
                    }
                }
                else{
                    c = get_next_token();
                    drop_marks(c);
                    for (temp_i = 0;  c[temp_i] != '\0' ; temp_i++) {
                        directive_memory[DC].w = get_word(c[temp_i]);
                        DC++;
                    }
                    directive_memory[DC] = get_word('\0');
                    DC++;
                }
            }
        }
        else{
            /* THIS LINE IS A INSTRUCTION LINE */
            if (is_label==TRUE){
                /* ADD TO THE SYMBOL TABLE */
            }
            /* search the operation name (mov, add) int the table */
            /* ask for the attributes depends on the operation youve got */
            /* set L to the number of operands */

            /* generate the code and add it to the ram */
            IC += L;
        }

        /* reset the variabels */
        L=0;









    }



}

