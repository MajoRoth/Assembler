#include "assembler.h"
#include <stdio.h>
#include <string.h>

OperationItem *get_operation_table(){
    OperationItem mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, jsr, red, prn, rts, stop, null;
        OperationItem *hash_table = (OperationItem *)malloc(OPT_SIZE * sizeof(OperationItem));
    /* initial all of the items and add them to the table */
    mov.name = "mov";
    mov.opcode = 0;
    mov.funct = 0;
    mov.words_num = 2;
    mov.legal_source[0] = 0;
    mov.legal_source[1] = 1;
    mov.legal_source[2] = 3;
    mov.legal_dest[0] = 1;
    mov.legal_dest[1] = 3;
    mov.legal_dest[2] = -1;
    hash_table[0] = mov;


    cmp.name = "cmp";
    cmp.opcode = 1;
    cmp.funct = 0;
    cmp.words_num = 2;
    cmp.legal_source[0] = 0;
    cmp.legal_source[1] = 1;
    cmp.legal_source[2] = 3;
    cmp.legal_dest[0] = 0;
    cmp.legal_dest[1] = 1;
    cmp.legal_dest[2] = 3;
    hash_table[1] = cmp;

    add.name = "add";
    add.opcode = 2;
    add.funct = 10;
    add.words_num = 2;
    add.legal_source[0] = 0;
    add.legal_source[1] = 1;
    add.legal_source[2] = 3;
    add.legal_dest[0] = 1;
    add.legal_dest[1] = 3;
    add.legal_dest[2] = -1;
    hash_table[2] = add;

    sub.name = "sub";
    sub.opcode = 2;
    sub.funct = 11;
    sub.words_num = 2;
    sub.legal_source[0] = 0;
    sub.legal_source[1] = 1;
    sub.legal_source[2] = 3;
    sub.legal_dest[0] = 1;
    sub.legal_dest[1] = 3;
    sub.legal_dest[2] = -1;
    hash_table[3] = sub;

    lea.name = "lea";
    lea.opcode = 4;
    lea.funct = 0;
    lea.words_num = 2;
    lea.legal_source[0] = 1;
    lea.legal_source[1] = -1;
    lea.legal_source[2] = -1;
    lea.legal_dest[0] = 1;
    lea.legal_dest[1] = 3;
    lea.legal_dest[2] = -1;
    hash_table[4] = lea;

    clr.name = "clr";
    clr.opcode = 5;
    clr.funct = 10;
    clr.words_num = 1;
    clr.legal_source[0] = -1;
    clr.legal_source[1] = -1;
    clr.legal_source[2] = -1;
    clr.legal_dest[0] = 1;
    clr.legal_dest[1] = 3;
    clr.legal_dest[2] = -1;
    hash_table[5] = clr;

    not.name = "not";
    not.opcode = 5;
    not.funct = 11;
    not.words_num = 1;
    not.legal_source[0] = -1;
    not.legal_source[1] = -1;
    not.legal_source[2] = -1;
    not.legal_dest[0] = 1;
    not.legal_dest[1] = 3;
    not.legal_dest[2] = -1;
    hash_table[6] = not;

    inc.name = "inc";
    inc.opcode = 5;
    inc.funct = 12;
    inc.words_num = 1;
    inc.legal_source[0] = -1;
    inc.legal_source[1] = -1;
    inc.legal_source[2] = -1;
    inc.legal_dest[0] = 1;
    inc.legal_dest[1] = 3;
    inc.legal_dest[2] = -1;
    hash_table[7] = inc;

    dec.name = "dec";
    dec.opcode = 5;
    dec.funct = 13;
    dec.words_num = 1;
    dec.legal_source[0] = -1;
    dec.legal_source[1] = -1;
    dec.legal_source[2] = -1;
    dec.legal_dest[0] = 1;
    dec.legal_dest[1] = 3;
    dec.legal_dest[2] = -1;
    hash_table[8] = dec;

    jmp.name = "jmp";
    jmp.opcode = 9;
    jmp.funct = 10;
    jmp.words_num = 1;
    jmp.legal_source[0] = -1;
    jmp.legal_source[1] = -1;
    jmp.legal_source[2] = -1;
    jmp.legal_dest[0] = 1;
    jmp.legal_dest[1] = 2;
    jmp.legal_dest[2] = -1;
    hash_table[9] = jmp;

    bne.name = "bne";
    bne.opcode = 9;
    bne.funct = 11;
    bne.words_num = 1;
    bne.legal_source[0] = -1;
    bne.legal_source[1] = -1;
    bne.legal_source[2] = -1;
    bne.legal_dest[0] = 1;
    bne.legal_dest[1] = 2;
    bne.legal_dest[2] = -1;
    hash_table[10] = bne;

    jsr.name = "jsr";
    jsr.opcode = 9;
    jsr.funct = 12;
    jsr.words_num = 1;
    jsr.legal_source[0] = -1;
    jsr.legal_source[1] = -1;
    jsr.legal_source[2] = -1;
    jsr.legal_dest[0] = 1;
    jsr.legal_dest[1] = 2;
    jsr.legal_dest[2] = -1;
    hash_table[11] = jsr;

    red.name = "red";
    red.opcode = 12;
    red.funct = 0;
    red.words_num = 1;
    red.legal_source[0] = -1;
    red.legal_source[1] = -1;
    red.legal_source[2] = -1;
    red.legal_dest[0] = 1;
    red.legal_dest[1] = 3;
    red.legal_dest[2] = -1;
    hash_table[12] = red;

    prn.name = "prn";
    prn.opcode = 13;
    prn.funct = 0;
    prn.words_num = 1;
    prn.legal_source[0] = -1;
    prn.legal_source[1] = -1;
    prn.legal_source[2] = -1;
    prn.legal_dest[0] = 0;
    prn.legal_dest[1] = 1;
    prn.legal_dest[2] = 3;
    hash_table[13] = prn;

    rts.name = "rts";
    rts.opcode = 14;
    rts.funct = 0;
    rts.words_num = 0;
    rts.legal_source[0] = -1;
    rts.legal_source[1] = -1;
    rts.legal_source[2] = -1;
    rts.legal_dest[0] = -1;
    rts.legal_dest[1] = -1;
    rts.legal_dest[2] = -1;
    hash_table[14] = rts;

    stop.name = "stop";
    stop.opcode = 15;
    stop.funct = 0;
    stop.words_num = 0;
    stop.legal_source[0] = -1;
    stop.legal_source[1] = -1;
    stop.legal_source[2] = -1;
    stop.legal_dest[0] = -1;
    stop.legal_dest[1] = -1;
    stop.legal_dest[2] = -1;
    hash_table[15] = stop;

    null.name = "null";
    hash_table[16] = null;

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
    SymbolNode *root = (SymbolNode *)malloc(sizeof(SymbolNode));
    root->attributes[0] = -1; /* add capacity for 2 later */
    root->value = -1;
    root->symbol = "\0";
    root->next = NULL;

    return root;
}

SymbolNode *add_symbol_node(char *symbol, int value, int attributes, SymbolNode *prev){
    /* add symbol node to an existing linked list */
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->attributes[0] = attributes; /* add capacity for 2 later */
    node->value = value;
    strcpy(node->symbol, symbol);
    prev->next = node;
    return node;
}

SymbolNode *get_last_node(SymbolNode *root){
    SymbolNode *last_node = root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}
