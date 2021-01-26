#include "word_process.h"

word *get_first_word(OperationItem *command, int source, int dest){
    word *first_word;
    first_word->bits += command->opcode;
    first_word->bits = first_word->bits << 4;
    first_word->bits += command->funct;
    first_word->bits = first_word->bits << 4;
    first_word->bits += dest;
    first_word->bits = first_word->bits << 2;
    first_word->bits += source;

    return first_word;
}


word *get_word_immediate(char *argument){
    /* returns word that represents the immediate operand*/
    char *operand;
    word *immediate_word = (word *)malloc(sizeof(word));
    int int_operand;
    if(is_comma(argument)){
        drop_comma(argument);
    }
    
    if(argument[1] == '-'){ /*in case operand is negative*/
        strcpy(operand, &argument[2])
        int_operand =-1 * atoi(operand);
    }
    else{
        strcpy(operand, &argument[1]);
        int_operand = atoi(operand);
    }
    
    immediate_word->bits += int_operand
    return immediate_word;
}

word *get_word_direct(char *argument,SymbolNode *root, int DCF){
    /* note that argument is a string - you need to process it IDO*/
    int i;
    word *label_word = (word *)malloc(sizeof(word));
    for (i=0; i<DCF; i++){/*search in the symbols table*/
        if(!strcmp(argument, root->symbol)){/*arg can only appear once in the table*/
            label_word += root->value;
        }
        root = root->next;
    /*REMEMBER - need to check if arg in the table: if label_word == 0 */
    }
    return label_word;
}

word *get_word_relative(char *argument){
    /* note that argument is a string - you need to process it AMIT*/
    word *relative_word = (word *)malloc(sizeof(word));

    /* not ready yet */

    return word;
}

word *get_word_register(char *argument){
    /* note that argument is a string - you need to process it AMIT*/
    int shift;
    word *register_word = (word *)malloc(sizeof(word));
    register_word->bits += 1;
    shift = argument[1] - '0'; /* convert argument[1] to int */
    register_word->bits = register_word->bits << shift;
    return register_word;
}