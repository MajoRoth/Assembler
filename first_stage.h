#ifndef ASSEMBLER_FIRST_STAGE_H
#define ASSEMBLER_FIRST_STAGE_H

#include <stdio.h>

#include "assembler_main.h"

int first_stage(FILE *file);
void directive_data_line();
void directive_string_line();
void add_instruction_words_2(OperationItem *command);
void add_instruction_word_1(OperationItem *command);
#endif
