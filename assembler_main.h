#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#define MAX_TABLE 4096
#define MAX_LINE 80
#define MAX_LABEL 31
#define OPT_SIZE 17

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct TableRow{
    word w;
    int ARE;
} TableRow;

typedef struct OperationItem{
    char *name;
    int opcode;
    int funct;
    int words_num; /* L */
    int legal_source[3];
    int legal_dest[3];
} OperationItem;

typedef struct SymbolNode{
    struct SymbolNode *next;
    char *symbol;
    int value;
    int attributes[2]; /* one line can have 2 symbols. for example data and extern */
} SymbolNode;

enum attribute {code, data, external, entry, string};
enum ARE {A, R, E};
enum boolean {FALSE, TRUE};

#endif
