#include "assembler_main.h"
#include "data_structures.h"
#include "first_stage.h"
#include "second_stage.h"
#include <stdlib.h>
#include <stdio.h>

int assembler (char *file_path){
    FILE *file = NULL;

    if (open_file(file_path, file)){
        initialize_data_structures();
        IC = 100;
        DC = 0;

        if (first_stage(file)){
            printf("STAGE 1 HAS BEEN DONE !!! \n");
            /* first stage finished - no errors */
            fseek(file, 0, SEEK_SET);
            second_stage(file);
        }
    }
}

/*
 * checks for correctness of the file name and tries to open the file
 * @return 1 - if the file opened and 0 - if an error occurred.
 */
int open_file(char *file_path, FILE *file){
    file = fopen(file_path,"r");
    if(!file){
        printf("file name is not valid");
        return 0;
    }
    return 1;
}

