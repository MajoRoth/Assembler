#include "error_handlers.h"
#include "data_structures.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

void COMMA_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL USE OF COMMAS", line);
}

void NAME_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL NAME OF VARIABLE", line);
}

void DOUBLE_DECLARATION_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: LABEL CAN BE DECLARED ONLY ONCE", line);
}

/*checks wether the register name is valid*/
void REGISTER_NAME_ERROR(int *flag, int line){
        *flag = TRUE; 
        printf("error in line %d: ILLEGAL REGISTER NAME", line);
    }
}

/*void CHECK_OPERANDS(enum boolean *flag, int line, char *source ,char *dest, OperationItem *command){
    if (command->words_num != 2){
        *flag = TRUE;
        printf("error in line %d: TOO MANY OPERANDS WERE GIVEN", line);
    }
function not finished
}*/




