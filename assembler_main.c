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
    char *directive;
    char *temp;

    int is_label = FALSE; /* flag weather the next line has a label */
    int is_direct = FALSE; /* flag weather the next line is a directive line */
    int directive = data;
    int attributes[2];

    while ((line = get_line(file_path)) != '\0'){
        i = is_label(line, label);
        if (label = is_label(line) != '\0'){
            is_label = TRUE;
        }

        if ((directive = is_directive(line, i, *directive)) != -1){
            is_direct = TRUE;
        }

        if (is_direct==TRUE){
            if(is_label==TRUE && directive==*data){
                /* deal with attributes array [2] later */
                /* add the line to the symbol table */
                add_symbol_node(label, DC, "data", get_last_node(root));
                /* add the command to the data table */

                    /* evaluate for cases - if string add each char in different word and finish with \0
                     * if str just put the numbers until there is no more numbers */
            }
        }
        else{
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

