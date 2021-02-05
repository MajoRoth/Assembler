#ifndef ASSEMBLER_DEBUG_TOOLS_H
#define ASSEMBLER_DEBUG_TOOLS_H
#include "assembler_main.h"


void print_word(word *w);

void print_table_symbol(SymbolNode *);

void print_table_row_ic(int i, int j);

void print_table_row_dc(int i, int j);

#endif 
