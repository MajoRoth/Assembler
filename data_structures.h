#ifndef ASSEMBLER_DATA_STRUCTURES_H
#define ASSEMBLER_DATA_STRUCTURES_H

enum {
    NONE = 16, IMMEDIATE = 8, DIRECT = 4,
    RELATIVE = 2, DIRECT_RED = 1, ILLEGAL_TYPE = 0
};

int get_funct_by_name(char *name, struct OperationItem hash_table[]);

int get_opcode_by_data(char *name, struct OperationItem hash_table[]);

SymbolNode *get_symbol_root();

SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);

SymbolNode *get_last_node();

int is_symbol_node_data(SymbolNode *node);

void add_ic(SymbolNode *root, int ICF);

void initialize_data_structures();

void free_data_structures();

#endif //ASSEMBLER_DATA_STRUCTURES_H
