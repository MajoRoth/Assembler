#ifndef ASSEMBLER_SECOND_STAGE_H
#define ASSEMBLER_SECOND_STAGE_H

#include "constants.h"

void COMMA_ERROR(int *flag, int line);

void NAME_ERROR(int *flag, int line);

void DOUBLE_DECLARATION_ERROR(int *flag, int line);

void LABEL_LENGTH_ERROR(int *flag, int line);

void ILLEGAL_LABEL_SYNTAX_ERROR(int *flag, int line);

void COMMAND_ERROR(int *flag, int line);

void LEGAL_OPERANDS_ERROR(int *flag, int line);

void OPERANDS_NUMBER_ERORR_1(int *flag, int line);

void OPERANDS_NUMBER_ERORR_2(int *flag, int line);

void REGISTER_NAME_ERROR(int *flag, int line);

void UNDEFINED_LABEL_ERROR(int *flag, char *label);

/*void CHECK_OPERANDS(int *flag, int line, char *source ,char *dest, OperationItem *command);*/

#endif