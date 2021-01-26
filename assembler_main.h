#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

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
    int operands[2];/* operands[0] is for the source and operands[1] is for the dest
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

void open_file(char *file_path, FILE *file);

TableRow *command_memory;
TableRow *directive_memory;
OperationItem operation_table;
OperationItem *operation_table;
SymbolNode *root;

int IC, DC;


#endif
