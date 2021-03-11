#include "error_handlers.h"
#include "data_structures.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

void COMMA_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL USE OF COMMAS\n", line);
}

void NAME_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL NAME OF VARIABLE\n", line);
}

void DOUBLE_DECLARATION_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: LABEL CAN BE DECLARED ONLY ONCE\n", line);
}

void LABEL_LENGTH_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: LABEL IS TOO LONG\n", line);
}

void ILLEGAL_LABEL_SYNTAX_ERROR(int *flag, int line){
    *flag = FALSE;
    if (line == UNKNOWN_LINE){
        printf("ILLEGAL LABEL SYNTAX\n");
    }
    else{
        printf("error in line %d: ILLEGAL LABEL SYNTAX\n", line);
    }
}

void COMMAND_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: COMMAND DOES NOT EXISTS\n", line);
}

void LEGAL_OPERANDS_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: ILLEGAL OPERAND FOR THIS COMMAND\n", line);
}

void OPERANDS_NUMBER_ERORR_1(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: TOO MANY OPERANDS\n", line);
}

void OPERANDS_NUMBER_ERORR_2(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: NOT ENOUGH OPERANDS\n", line);
}

/*checks wether the register name is valid*/
void REGISTER_NAME_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: ILLEGAL REGISTER NAME\n", line);
    }

void UNDEFINED_LABEL_ERROR(int *flag, char *label){
    *flag = TRUE;
    printf("UNDEFINED LABEL %s\n", label);
}



