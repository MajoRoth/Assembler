#include "assembler_main.h"
#include "first_stage.h"
#include "second_stage.h"
#include "constants.h"
#include "debug_tools.h"
#include <stdlib.h>
#include <stdio.h>

int assembler (char *file_path){
    FILE *file = NULL;
    printf("entered assembler_main.c\n");

    if (open_file(file_path, &file)){
        initialize_data_structures();
        IC = 100;
        DC = 0;

        if (first_stage(file)){
            printf("STAGE 1 HAS BEEN DONE !!! \n");
            add_ic(root, IC);
            print_table_symbol(root);
            merge_ic_dc();
            /* first stage finished - no errors */
            fseek(file, 0, SEEK_SET);
            second_stage(file);
        }
        fclose(file);
    }
    return 1;
}

/*
 * checks for correctness of the file name and tries to open the file
 * @return 1 - if the file opened and 0 - if an error occurred.
 */
int open_file(char *file_path, FILE **file){
    char file_path_as[MAX_LABEL];
    strcpy(file_path_as, file_path);
    strcat(file_path_as, ".as");
    *file = fopen(file_path_as,"r");
    if(!*file){
        printf("file name is not valid\n");
        return 0;
    }
    printf("%s opened sucessfully\n", file_path);
    return 1;
}

/*
 *  allocates memory and initialize the program data structures
 */
void initialize_data_structures(){
    command_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    directive_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    root = get_symbol_root();
}

/*
 *  free all of the program's allocated memory
 */
void free_data_structures(){
    SymbolNode *node = root, *next_node;
    next_node = root->next;
    free(command_memory);
    free(directive_memory);
    free(root);
    /* free the linked list */
    while (node->next != NULL){
        next_node = node->next;
        free(node);
        node = next_node;
    }
}

void merge_ic_dc(){
    int i;
    for (i=0; i<DC; i++){
        command_memory[IC+i] = directive_memory[i];
    }
    free(directive_memory);
}