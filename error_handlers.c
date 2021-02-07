#include "error_handlers.h"
#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>

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
/*function not finished*/
}
/*checks wether the label has already been declared
call this funcyion before you add new label to symbol table*/
void DOUBLE_DECLARATION_ERROR(enum boolean *flag, int line, SymbolNode *root, char *label){
    int b = 0;
    SymbolNode *node = root;
    while(node->next != NULL && b == 0){
        if (!strcmy(node->symbol, label){
            b=1
            *flag = TRUE;
            printf("error in line %d: LABEL CAN BE DECLARED ONLY ONCE", line);
        }
        node = node->next;
    }
}

/*checks wether the register name is valid
call this function inside operand_address_method() in case of a register adress*/
void REGISTER_NAME_ERROR(enum boolean *flag, int line, char *argument){
    if (argument[1] < 48 && argument[1] > 55){
        *flag = TRUE;
        printf("error in line %d: ILLEGAL REGISTER NAME", line);
    }
}


