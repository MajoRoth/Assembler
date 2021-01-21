#include "assembler.h"

word *get_first_word(OperationItem *command, int source, int dest){
    word *first_word;
    first_word->bits += command->opcode;
    first_word->bits << 4;
    first_word->bits += command->funct;
    first_word->bits << 4;
    first_word->bits += dest;
    first_word->bits << 2;
    first_word->bits += source;

    return first_word;
}


word *get_word_immediate(char *argument){
    /* note that argument is a string - you need to process it  IDO*/

}

word *get_word_direct(char *argument){
    /* note that argument is a string - you need to process it IDO*/

}

word *get_word_relative(char *argument){
    /* note that argument is a string - you need to process it AMIT*/

}

word *get_word_register(char *argument){
    /* note that argument is a string - you need to process it AMIT*/

}