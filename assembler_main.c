#include "assembler_main.h"
#include "first_stage.h"
#include "second_stage.h"
#include "constants.h"
#include "debug_tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * the main logic of the assembler is here. opens file, calls to first stage,
 * merge ic and dc and calls to second stage
 * @param file_path
 * @return None
 */
int assembler (char *file_path){
    FILE *file = NULL;

    if (open_file(file_path, &file)){
        initialize_data_structures();
        IC = 100;
        DC = 0;

        if (first_stage(file)){
            add_ic(root, IC);
            merge_ic_dc();
            fseek(file, 0, SEEK_SET);
            second_stage(file, file_path);
        }
        fclose(file);
        free_data_structures();
    }
    return 1;
}


/**
 * check for correctness of the file name and tries to open it
 * @param file_path
 * @param file
 * @return 1 if succeed 0 if dosen't
 */
int open_file(char *file_path, FILE **file){
    char file_path_as[MAX_LABEL];
    strcpy(file_path_as, file_path);
    strcat(file_path_as, ".as");
    *file = fopen(file_path_as,"r");
    if(!*file){
        printf("ERROR: %s is invalid file name\n", file_path);
        return 0;
    }
    return 1;
}

/**
 * allocates memory to the global data structures
 */
void initialize_data_structures(){
    command_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    directive_memory = (TableRow *)malloc(MAX_TABLE * sizeof(TableRow));
    root = get_symbol_root();
    external_list_root = get_external_list_root();
}

/**
 * free the memory of the global data structures
 */
void free_data_structures(){
    SymbolNode *node = root, *next_node;
    External_list_Node *node1 = external_list_root, *next_node1;
    next_node = root->next;
    free(command_memory);
    /* free the linked list */
    while (node->next != NULL){
        next_node = node->next;
        free(node);
        node = next_node;
    }

    while (node1->next != NULL){
        next_node1 = node1->next;
        free(node1);
        node1 = next_node1;
    }
}

/**
 * merge the ic and the dc after the first stage
 */
void merge_ic_dc(){
    int i;
    for (i=0; i<DC; i++){
        command_memory[IC+i] = directive_memory[i];
    }
    free(directive_memory);
}


