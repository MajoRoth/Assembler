#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H
#include <stdio.h>
#include "data_structures.h"
enum ARE {A, R, E};
enum boolean {FALSE, TRUE};

int assembler (char *file_path);
int open_file(char *file_path, FILE **file);

TableRow *command_memory;
TableRow *directive_memory;
OperationItem *operation_table;
SymbolNode *root;

void initialize_data_structures();

void free_data_structures();

int IC, DC;


#endif
