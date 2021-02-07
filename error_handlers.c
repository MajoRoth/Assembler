#include "error_handlers.h"
#include "data_structures.h"
#include <stdio.h>

void COMMA_ERROR(enum boolean *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL USE OF COMMAS", line);
}

void NAME_ERROR(enum boolean *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL NAME OF VARIABLE", line);
}

void CHECK_OPERANDS(enum boolean *flag, int line, char *source ,char *dest, OperationItem *command){
    if (command->words_num != 2){
        *flag = TRUE;
        printf("error in line %d: TOO MANY OPERANDS WERE GIVEN", line);
    }
/*function not done*/
}


