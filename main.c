#include "assembler_main.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* get the names from the command line as args
     * and send each one to assembler_main.c
     */
    int i;
    for (i=0; i<argc; i++){
        assembler(argv[i]);
    }
    return 0;
}


