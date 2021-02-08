#include "data_structures.h"
#include "constants.h"
#include "text_process.h"
#include "debug_tools.h"
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

void get_command(char *argument, OperationItem **p, OperationItem *table){
    /* ignores spaces and returns the next command */
    int i;
    for (i=0; i< 16; i++){
        if (!strcmp(table[i].name, argument)){
            *p = table+i;
            return;
        }
    }
    *p = table+16;
}

/* initialize symbols table - linked list */

SymbolNode *get_symbol_root(){
    /* init a new symbols linked list */
    SymbolNode *root = (SymbolNode *)malloc(sizeof(SymbolNode));
    root->attribute = -1; /* add capacity for 2 later */
    root->value = -1;
    root->symbol = "\0";
    root->next = NULL;

    return root;
}

SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev){
    /* add symbol node to an existing linked list */
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->attribute = attribute;
    node->value = value;
    node->symbol = (char *)malloc(MAX_LABEL);
    strcpy(node->symbol, symbol);
    prev->next = node;
    return node;
}

SymbolNode *get_last_node(SymbolNode *root){
    SymbolNode *last_node = root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

int is_symbol_node_data(SymbolNode *node){
    /* checks if a node has "code" attribute */
    if (node->attribute == data) return 1;
    return 0;
}

int add_entry_to_symbol(char *label){
    SymbolNode *node = root;
    while (node->next != NULL){
        node = node->next;
        if (strcmp(node->symbol, label) == 0)
        {
            node->attribute += entry;
            return 1;
        }
    }
    return 0;
}


void add_ic(SymbolNode *root, int ICF){
    SymbolNode *node;
    node = root;
    while (node->next != NULL){
        if (is_symbol_node_data(node)){
            node->value += ICF;
        }
        node = node->next;
    }
}


/* word process */

word *get_first_word(OperationItem *command, int source, int dest){
    word *first_word = (word *)malloc(sizeof(word));
    first_word->bits = 0;
    first_word->bits += command->opcode;
    first_word->bits = first_word->bits << 4;
    first_word->bits += command->funct;
    first_word->bits = first_word->bits << 2;
    first_word->bits += source;
    first_word->bits = first_word->bits << 2;
    first_word->bits += dest;
    printf("first word %s source: %d, dest: %d, word: ", command->name, source, dest);
    print_word(first_word);
    return first_word;
}


word *get_word_immediate(char *argument){
    /* returns word that represents the immediate operand*/
    char *operand = (char *)malloc(sizeof(char)* MAX_ARGUMENT);
    word *immediate_word = (word *)malloc(sizeof(word));
    int int_operand;
    if(is_comma(argument)){
        drop_comma(argument);
    }

    if(argument[1] == '-'){ /*in case operand is negative*/
        strcpy(operand, &argument[2]);
        int_operand =-1 * atoi(operand);
    }
    else{
        strcpy(operand, &argument[1]);
        int_operand = atoi(operand);
    }

    immediate_word->bits += int_operand;
    return immediate_word;
}

word *get_word_direct(char *argument, SymbolNode *root, int DCF){
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

    return relative_word;
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

word *get_word(int i) {
    word *w = (word *)malloc(sizeof(word));
    w->bits = i;
    return w;
}
