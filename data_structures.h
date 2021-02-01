#ifndef ASSEMBLER_DATA_STRUCTURES_H
#define ASSEMBLER_DATA_STRUCTURES_H
enum {
    NONE = 16, IMMEDIATE = 8, DIRECT = 4,
    RELATIVE = 2, DIRECT_REG = 1, ILLEGAL_TYPE = 0
};

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct TableRow{
    word *w;
    int ARE;
} TableRow;

typedef struct SymbolNode{
    struct SymbolNode *next;
    char *symbol;
    int value;
    int attributes[2]; /* one line can have 2 symbols. for example data and extern */
} SymbolNode;

typedef struct OperationItem{
    char *name;
    int opcode;
    int funct;
    int words_num; /* L */
    int operands[2];/* operands[0] is for the source and operands[1] is for the dest */
} OperationItem;

int get_funct_by_name(char *name, OperationItem *hash_table);

int get_opcode_by_data(char *name, OperationItem *hash_table);

void get_command(char *argument, OperationItem *p, OperationItem *table);

SymbolNode *get_symbol_root();

SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);

SymbolNode *get_last_node();

int is_symbol_node_data(SymbolNode *node);

void add_ic(SymbolNode *root, int ICF);

void initialize_data_structures();

void free_data_structures();

/* WORD PROCESS */
word *get_first_word(OperationItem *command, int source, int dest);

word *get_word_immediate(char *argument);

word *get_word_direct(char *argument, SymbolNode *root, int DCF);

word *get_word_relative(char *argument);

word *get_word_register(char *argument);

word *get_word(int i);


#endif 
