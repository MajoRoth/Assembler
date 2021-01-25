#ifndef ASSEMBLER_DATA_STRUCTURES_H
#define ASSEMBLER_DATA_STRUCTURES_H




OperationItem *get_operation_table();

int get_funct_by_name(char *name, struct OperationItem hash_table[]);

int get_opcode_by_data(char *name, struct OperationItem hash_table[]);

SymbolNode *get_symbol_root();

SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);

SymbolNode *get_last_node(SymbolNode *root);

int is_symbol_node_code(SymbolNode *node);

void add_icf(SymbolNode *root, int ICF);

#endif //ASSEMBLER_DATA_STRUCTURES_H
