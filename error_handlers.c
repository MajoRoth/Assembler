#include "error_handlers.h"
#include <stdio.h>

void COMMA_ERROR(enum boolean *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL USE OF COMMAS", line);
}

void NAME_ERROR(enum boolean *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL NAME OF VARIABLE", line);
}


