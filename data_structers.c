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
    /* -1 represents None */
    mov.name = "mov";
    mov.opcode = 0;
    mov.funct = -1;
    mov.words_num = 2;
    mov.legal_source = {0,1,3};
    mov.legal_dest = {1,3};

    cmp.name = "cmp";
    cmp.opcode = 1;
    cmp.funct = -1;
    cmp.words_num = 2;
    cmp.legal_source = {0,1,3};
    cmp.legal_dest = {0,1,3};

    add.name = "add";
    add.opcode = 2;
    add.funct = 10;
    add.words_num = 2;
    add.legal_source = {0,1,3};
    add.legal_dest = {1,3};

    sub.name = "sub";
    sub.opcode = 2;
    sub.funct = 11;
    sub.words_num = 2;
    sub.legal_source = {0,1,3};
    sub.legal_dest = {1,3};

    lea.name = "lea";
    lea.opcode = 4;
    lea.funct = -1;
    lea.words_num = 2;
    lea.legal_source = {1};
    lea.legal_dest = {1,3};

    clr.name = "clr";
    clr.opcode = 5;
    clr.funct = 10;
    clr.words_num = 1;
    clr.legal_source = {-1};
    clr.legal_dest = {1,3};

    not.name = "not";
    not.opcode = 5;
    not.funct = 11;
    not.words_num = 1;
    not.legal_source = {-1};
    not.legal_dest = {1,3};

    inc.name = "inc";
    inc.opcode = 5;
    inc.funct = 12;
    inc.words_num = 1;
    inc.legal_source = {-1};
    inc.legal_dest = {1,3};

    dec.name = "dec";
    dec.opcode = 5;
    dec.funct = 13;
    dec.words_num = 1;
    dec.legal_source = {-1};
    dec.legal_dest = {1,3};

    jmp.name = "jmp";
    jmp.opcode = 9;
    jmp.funct = 10;
    jmp.words_num = 1;
    jmp.legal_source = {-1};
    jmp.legal_dest = {1,2};

    bne.name = "bne";
    bne.opcode = 9;
    bne.funct = 11;
    bne.words_num = 1;
    bne.legal_source = {-1};
    bne.legal_dest = {1,2};

    jsr.name = "jsr";
    jsr.opcode = 9;
    jsr.funct = 12;
    jsr.words_num = 1;
    jsr.legal_source = {-1};
    jsr.legal_dest = {1,2};

    red.name = "red";
    red.opcode = 12;
    red.funct = -1;
    red.words_num = 1;
    red.legal_source = {-1};
    red.legal_dest = {1,3};

    prn.name = "prn";
    prn.opcode = 13;
    prn.funct = -1;
    prn.words_num = 1;
    prn.legal_source = {-1};
    prn.legal_dest = {0,1,3};

    rts.name = "rts";
    rts.opcode = 14;
    rts.funct = -1;
    rts.words_num = 0;
    rts.legal_source = {-1};
    rts.legal_dest = {-1};

    stop.name = "stop";
    stop.opcode = 15;
    stop.funct = -1;
    stop.words_num = 0;
    stop.legal_source = {-1};
    stop.legal_dest = {-1};

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
    return  -1;
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

SymbolNode *get_symbol_root(){
    /* init a new symbols linked list */
    SymbolNode root;
    root.attributes = NULL; /* add capacity for 2 later */
    root.value = *NULL;
    root.symbol = NULL;
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

SymbolNode *get_last_node(SymbolNode *root){
    SymbolNode *last_node = *root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

/* data table */
SymbolNode *get_symbol_root(){
    /* init a new symbols linked list */
    SymbolNode root;
    root.attributes = NULL; /* add capacity for 2 later */
    root.value = *NULL;
    root.symbol = NULL;
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

SymbolNode *get_last_node(SymbolNode *root){
    SymbolNode *last_node = *root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

