#ifndef ASSEMBLER_FIRST_STAGE_H
#define ASSEMBLER_FIRST_STAGE_H

#include <stdio.h>

#include "assembler_main.h"
#include "constants.h"

int first_stage(FILE *file);
void directive_data_line();
void directive_string_line();
void add_instruction_words_2(OperationItem *command, int line_number);
void add_instruction_word_1(OperationItem *command, int line_number);
void free_temp(char *line, char *argument, char *label);

void CHECK_DOUBLE_DECLARATION(enum boolean *flag, int line, SymbolNode *root, char *label);
void CHECK_REGISTER_NAME(int *flag, int line, char *argument);
#endif
