#ifndef ASSEMBLER_FIRST_STAGE_H
#define ASSEMBLER_FIRST_STAGE_H

#include <stdio.h>

int first_stage(FILE file);
void directive_data_line();
void directive_string_line();
void add_instruction_words_2();
void add_instruction_word_1();
#endif
