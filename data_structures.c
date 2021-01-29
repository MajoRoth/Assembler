#include "data_structures.h"
#include "assembler_main.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_funct_by_name(char *name, OperationItem *hash_table){
    int i;
    for (i=0; i < 16; i++) {
        if (!strcmp(hash_table[i].name, name)){
            return hash_table[i].funct;
        }
    }
    return  -1;
}

int get_opcode_by_name(char *name, OperationItem *hash_table){
    int i;
    for (i=0; i < 16; i++) {
        if (!strcmp(hash_table[i].name, name)){
            return hash_table[i].opcode;
        }
    }
    return -1;
}

/* initialize symbols table - linked list */

SymbolNode *get_symbol_root(){
    /* init a new symbols linked list */
    SymbolNode *root = (SymbolNode *)malloc(sizeof(SymbolNode));
    root->attributes[0] = -1; /* add capacity for 2 later */
    root->value = -1;
    root->symbol = "\0";
    root->next = NULL;

    return root;
}

SymbolNode *add_symbol_node(char *symbol, int value, int attributes, SymbolNode *prev){
    /* add symbol node to an existing linked list */
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->attributes[0] = attributes; /* add capacity for 2 later */
    node->value = value;
    strcpy(node->symbol, symbol);
    prev->next = node;
    return node;
}

SymbolNode *get_last_node(){
    SymbolNode *last_node = root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

int is_symbol_node_data(SymbolNode *node){
    /* checks if a node has "code" attribute */
    if (node->attributes[0] == data) return 1;
    return 0;
}


void add_ic(SymbolNode *root, int ICF){
    SymbolNode *node = root;
    while (node->next != NULL){
        if (is_symbol_node_data(node)){
            node->value += ICF;
        }
        node = node->next;
    }
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
    SymbolNode *node = root, next_node = root->next;
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
