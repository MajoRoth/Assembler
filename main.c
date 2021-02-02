#include "assembler_main.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* get the names from the command line as args
     * and send each one to assembler_main.c
     */
    int i;
    printf("entered main.c\n");
    if (argc==1)
    {
        printf("specify at least 1 file\n");
        return 0;
    }

    for (i=1; i<argc; i++){
        assembler(argv[i]);
    }
    return 0;
}


