#ifndef ASSEMBLER_SECOND_STAGE_H
#define ASSEMBLER_SECOND_STAGE_H

#include "constants.h"

void COMMA_ERROR(int *flag, int line);

void NAME_ERROR(int *flag, int line);

void DOUBLE_DECLARATION_ERROR(int *flag, int line);

void LABEL_LENGTH_ERROR(int *flag, int line);

void REGISTER_NAME_ERROR(int *flag, int line);

/*void CHECK_OPERANDS(int *flag, int line, char *source ,char *dest, OperationItem *command);*/

#endif