//
// Created by Amit Roth on 09/01/2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#endif //ASSEMBLER_ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TABLE 4096
#define MAX_LINE 80;
#define MAX_LABEL 31;
#define MAX_DIRECTIVE 6;
#define MAX_COMMAND 4;

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct TableRow{
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

enum attribute {code, data, external, entry, string};
enum ARE {A, R, E};
enum boolean {FALSE, TRUE};


/* data structures functions */
OperationItem *get_operation_table();
int get_funct_by_name(char *name, struct OperationItem hash_table[]);
int get_opcode_by_name(char *name, struct OperationItem hash_table[]);
SymbolNode *get_symbol_root();
SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);
SymbolNode *get_last_node(SymbolNode *root);

/* text process */
char *get_line();
int is_directive(char *line);
char *get_next_token();
void drop_comma(char *str);
word *get_word(int i);

