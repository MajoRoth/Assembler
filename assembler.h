//
// Created by Amit Roth on 09/01/2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#endif //ASSEMBLER_ASSEMBLER_H

#include <stdio.h>
#include <string.h>

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct RamNode{
    word w;
    int ARE;
} RamNode;

typedef struct OperationItem{
    char *name;
    int opcode;
    int funct;
} OperationItem;

typedef struct SymbolNode{
    SymbolNode *next;
    char *symbol;
    int value;
    int attributes[2]; // one line can have 2 symbols. for example data and extern
} SymbolNode;

enum attribute {code, data, external, entry};
enum ARE {A, R, E};
enum boolean {FALSE, TRUE};


/* data structures functions */
OperationItem *get_operation_table();
int get_funct_by_name(char *name, struct OperationItem hash_table[]);
int get_opcode_by_name(char *name, struct OperationItem hash_table[]);
SymbolNode *get_symbol_root(char *symbol, int value, int attribute);
SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);

/* text process */
char *get_line();
int is_directive(char *line);

