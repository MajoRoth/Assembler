//
// Created by Amit Roth on 09/01/2021.
//
#include "assembler.h"

int assembler (char *file_path){
    /* declaring data types */
    struct RamNode RAM[4096];
    struct OperationItem hash_table[16] = get_operation_table();
    SymbolNode root;

    int IC = 100;
    int DC = 0;
    int L = 0;
    char line[80];
    char *label;
    char *directive;

    int is_label = FALSE; /* flag weather the next line has a label */
    int is_directive = FALSE; /* flag weather the next line is a directive line */
    int directive = data;
    int attributes[2];

    while ((line = get_line()) != '\0'){
        if (label = is_label(line) != '\0'){
            is_label = TRUE;
        }

        if ((directive = is_directive(line)) != -1){
            is_directive = TRUE;
        }

        if (is_directive==TRUE){
            if(is_label==TRUE && directive==data){
                /* deal with attributes array [2] later */
                if (DC==0){
                    root = get_symbol_root(label, IC, data) /* enter the 3 params needed */
                }
                else{
                    add_symbol_node(label, IC, data, root); /* enter the 3 params needed */
                }
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

