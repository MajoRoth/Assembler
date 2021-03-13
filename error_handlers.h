#ifndef ASSEMBLER_SECOND_STAGE_H
#define ASSEMBLER_SECOND_STAGE_H

#include "constants.h"

/**
 * COMMA ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void COMMA_ERROR(int *flag, int line);

/**
 * NAME ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void NAME_ERROR(int *flag, int line);

/**
 * DOUBLE DECLARATION ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void DOUBLE_DECLARATION_ERROR(int *flag, int line);

/**
 * LABEL LENGTH ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void LABEL_LENGTH_ERROR(int *flag, int line);

/**
 * ILLEGAL LABEL SYNTAX ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void ILLEGAL_LABEL_SYNTAX_ERROR(int *flag, int line);

/**
 * COMMAND ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void COMMAND_ERROR(int *flag, int line);

/**
 * LEGAL OPERANDS ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void LEGAL_OPERANDS_ERROR(int *flag, int line);

/**
 * OPERANDS NUMBER ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void OPERANDS_NUMBER_ERORR_1(int *flag, int line);

/**
 * OPERANDS NUMBER ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void OPERANDS_NUMBER_ERORR_2(int *flag, int line);

/**
 * REGISTER NAME ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void REGISTER_NAME_ERROR(int *flag, int line);

/**
 * UNDEFINED LABEL ERROR
 * @param flag - a pointer to error flag
 * @param label - the label
 */
void UNDEFINED_LABEL_ERROR(int *flag, char *label);

/**
 * FILE NAME ERROR
 * @param file_name - the name of the invalid file
 */
void FILE_NAME_ERROR(char *file_name);

#endif

