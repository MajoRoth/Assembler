#ifndef ASSEMBLER_DEBUG_TOOLS_H
#define ASSEMBLER_DEBUG_TOOLS_H
#include "assembler_main.h"

/**
 * prints a word in binary
 */
void print_word(word *w);

/**
 * prints ic
 */
void print_table_row_ic(int i, int j);

/**
 * prints dc
 */
void print_table_row_dc(int i, int j);

/**
 * prints symbol list
 */
void print_table_symbol(SymbolNode *);

#endif 
