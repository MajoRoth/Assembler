#ifndef ASSEMBLER_FIRST_STAGE_H
#define ASSEMBLER_FIRST_STAGE_H
#include <stdio.h>
#include "assembler_main.h"
#include "constants.h"

/**
 * The skeleton of first stage - contains the logic and the
 * calls to to the side functions of first_stage.c
 * @param file - a file pointer
 * @return 1 if no errors 0 if were
 */
int first_stage(FILE *file);

/**
 * adds to directive_memory[] the word following by data declaration
 * @param line_number - a pointer to the current line number
 */
void directive_data_line();

/**
 * adds to directive_memory[] the word following by string declaration
 */
void directive_string_line();

/**
 * adds to command_memory for words which L=2
 * @param command - pointer to the command
 */
void add_instruction_words_2(OperationItem *command, int line_number);

/**
 * adds to command_memory for words which L=1
 * @param command - pointer to the command
 * @param line_number - curren row number in the file 
 */
void add_instruction_word_1(OperationItem *command, int line_number);

/**
 * free the temporary variables
 * @param line
 * @param argument
 * @param label
 */
void free_temp(char *line, char *argument, char *label);

void CHECK_DOUBLE_DECLARATION(int *flag, int line, SymbolNode *root, char *label);
void CHECK_REGISTER_NAME(int *flag, int line, char *argument);
void CHECK_LABEL_LENGTH(int *flag, int line, char *label);
void CHECK_COMMAND(int *flag, int line, OperationItem *command);
void CHECK_LEGAL_OPERANDS(int *flag, int line, int dest, int source, OperationItem *command);
#endif

