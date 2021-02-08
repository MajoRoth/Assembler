#ifndef ASSEMBLER_SECOND_STAGE_H
#define ASSEMBLER_SECOND_STAGE_H

void COMMA_ERROR(int *flag, int line);

void NAME_ERROR(int *flag, int line);

/*void CHECK_OPERANDS(int *flag, int line, char *source ,char *dest, OperationItem *command);*/

/*void DOUBLE_DECLARATION_ERROR(int, int line, SymbolNode *root, char *label);*/

void REGISTER_NAME_ERROR(int *flag, int line, char *argument);

#endif