//
// Created by Amit Roth on 11/01/2021.
//
#include "assembler.h"

struct OperationItem *get_operation_table(){
    struct OperationItem mov, cmp, add, sub, lea, clr, not, ine, dec, jmp, bne, jsr, red, prn, rts, stop;
    struct OperationItem* hash_table[16];
    // initial all of the items and add them to the table

    hash_table = {mov, cmp, add, sub, lea, clr, not, ine, dec, jmp, bne, jsr, red, prn, rts, stop};
    return hash_table;
}

int get_funct_by_name(){

}

int get_opcode_by_name(){

}

/* initialize symbols table - linked list */

