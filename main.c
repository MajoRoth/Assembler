#include "assembler_main.h"
#include <stdio.h>

/**
 * Main function for Assembler. gets the input from the command line and calls to assembler.
 * @param argc
 * @param argv
 * @return None
 */
int main(int argc, char *argv[]) {
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


