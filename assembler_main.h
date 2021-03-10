#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H
#include <stdio.h>
#include "data_structures.h"

/**
 * global variables
 */
TableRow *command_memory;
TableRow *directive_memory;
OperationItem *operation_table;
SymbolNode *root;
External_list_Node *external_list_root;

int IC, DC;

/**
 * the main logic of the assembler is here. opens file, calls to first stage,
 * merge ic and dc and calls to second stage
 * @param file_path
 * @return None
 */
int assembler (char *file_path);

/**
 * check for correctness of the file name and tries to open it
 * @param file_path
 * @param file
 * @return 1 if succeed 0 if dosen't
 */
int open_file(char *file_path, FILE **file);

/**
 * allocates memory to the global data structures
 */
void initialize_data_structures();

/**
 * free the memory of the global data structures
 */
void free_data_structures();

/**
 * merge the ic and the dc after the first stage
 */
void merge_ic_dc();



#endif
