//
// Created by Amit Roth on 11/01/2021.
//
#include "assembler.h"
#include <stdio.h>
#include <string.h>

OperationItem *get_operation_table(){
    struct OperationItem mov, cmp, add, sub, lea, clr, not, ine, dec, jmp, bne, jsr, red, prn, rts, stop;
    struct OperationItem hash_table[16];
    // initial all of the items and add them to the table

    hash_table = {mov, cmp, add, sub, lea, clr, not, ine, dec, jmp, bne, jsr, red, prn, rts, stop};
    return hash_table;
}

int get_funct_by_name(char *name, struct OperationItem hash_table[]){
    int i;
    for (i=0; i < 16; i++) {
        if (!strcmp(hash_table[i].name, name)){
            return hash_table[i].funct;
        }
    }
    return -1;
}

int get_opcode_by_name(char *name, struct OperationItem hash_table[]){
    int i;
    for (i=0; i < 16; i++) {
        if (!strcmp(hash_table[i].name, name)){
            return hash_table[i].opcode;
        }
    }
    return -1;
}

/* initialize symbols table - linked list */

SymbolNode *get_symbol_root(char *symbol, int value, int attributes){
    /* init a new symbols linked list */
    SymbolNode root;
    root.attributes = attributes; /* add capacity for 2 later */
    root.value = value;
    root.symbol = symbol;
    root.next = NULL;

    return root;
}

SymbolNode *add_symbol_node(char *symbol, int value, int attributes, SymbolNode *prev){
    /* add symbol node to an existing linked list */
    SymbolNode node;
    node.attributes = attributes; /* add capacity for 2 later */
    node.value = value;
    node.symbol = symbol;
    prev->next = node;
    return root;
}

