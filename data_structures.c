#include "data_structures.h"
#include "constants.h"
#include "text_process.h"
#include "debug_tools.h"
#include "error_handlers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * searching command and returning her pointer in **p
 * @param argument - char *
 * @param p - the operation that returns
 * @param table - the table head
 */
void get_command(char *argument, OperationItem **p, OperationItem *table){
    int i;
    for (i=0; i< 16; i++){
        if (!strcmp(table[i].name, argument)){
            *p = table+i;
            return;
        }
    }
    *p = table+16;
}

/**
 * searching command_L and returning her pointer in **p
 * @param argument - char *
 * @param p - the operation_L that returns
 * @param table - the table head
 */
void get_command_L(char *argument, OperationL **p, OperationL *table){
    int i;
    for (i=0; i< 16; i++){
        if (!strcmp(table[i].name, argument)){
            *p = table+i;
            return;
        }
    }
    *p = table+16;
}


/**
 * initialize a list
 * @return a pointer to the root
 */
SymbolNode *get_symbol_root(){
    SymbolNode *root = (SymbolNode *)malloc(sizeof(SymbolNode));
    root->attribute = -1;
    root->value = -1;
    root->symbol = "\0";
    root->next = NULL;
    return root;
}

/**
 * adds a node to the linked list
 * @param symbol - char *
 * @param value  - int
 * @param attribute - int
 * @param prev - the node you want to concatenate to
 * @return a pointer to the new node
 */
SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev){
    /* add symbol node to an existing linked list */
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->attribute = attribute;
    node->value = value;
    node->symbol = (char *)malloc(MAX_LABEL);
    node->next = NULL;
    strcpy(node->symbol, symbol);
    prev->next = node;
    return node;
}

/**
 * get the last node from a linked list
 * @param root
 * @return a pointer to the last node
 */
SymbolNode *get_last_node(SymbolNode *root){
    SymbolNode *last_node = root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

/**
 * initialize a list
 * @return a pointer to the root
 */
External_list_Node *get_external_list_root(){
     /* init a new symbols linked list */
    External_list_Node *root = (External_list_Node *)malloc(sizeof(External_list_Node));
     root->value = -1;
    root->symbol = "\0";
    root->next = NULL;
    return root;
}

/**
 * adds a node to the linked list
 * @param symbol - char *
 * @param value  - int
 * @param attribute - int
 * @param prev - the node you want to concatenate to
 * @return a pointer to the new node
 */
External_list_Node *add_external_list_node(char *symbol, int value, External_list_Node *prev){
    /* add symbol node to an existing linked list */
    External_list_Node *node = (External_list_Node *)malloc(sizeof(External_list_Node));
    node->value = value;
    node->symbol = (char *)malloc(MAX_LABEL);
    node->next = NULL;
    strcpy(node->symbol, symbol);
    prev->next = node;
    return node;
}

/**
 * get the last node from a linked list
 * @param root
 * @return a pointer to the last node
 */
External_list_Node *get_last_external_list_node(External_list_Node *root){
    External_list_Node *last_node = root;
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    return last_node;
}

/**
 * check if a node has data attribute
 * @param node
 * @return 1 if true 0 if false
 */
int is_symbol_node_data(SymbolNode *node){
    if (node->attribute == data) return 1;
    return 0;
}

/**
 * searches a label in the symbol table
 * @param label
 * @param root
 * @param EXT_VAR
 * @return the value if it worked -1 if didn't
 */
int search_symbol_table(char *label, SymbolNode *root, int *EXT_VAR){
    SymbolNode *node = root;
    while(node->next != NULL){
        node = node->next;
        if (!strcmp(label,node->symbol)){
            if (node->attribute & 4)
            {
                *EXT_VAR = TRUE;
            }
            return node->value;
        }
    }
    /*if search failed*/
    return -1;
}

/**
 * add entry attribute to symbol
 * @param label
 * @return 1 if worked 0 if didn't
 */
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

/**
 * iterates through the symbol list and adds ICF to data labels
 * @param root
 * @param ICF
 */
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


/**
 * creating the "first word" of each operation
 * @param command
 * @param source
 * @param dest
 * @return a pointer to the word
 */
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
    return first_word;
}

/**
 * create a word by the immediate addressing method
 * @param argument
 * @return a pointer to the word
 */
word *get_word_immediate(char *argument){
    char *operand = (char *)malloc(sizeof(char)* MAX_ARGUMENT);
    word *immediate_word = (word *)malloc(sizeof(word));
    int int_operand;
    if(is_comma(argument)){
        drop_comma(argument);
    }

    if(argument[1] == '-'){
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

/**
 * create a word by the direct addressing method
 * @param argument
 * @param root
 * @param flag
 * @param EXT_VAR
 * @return a pointer to the word
 */
word *get_word_direct(char *argument, SymbolNode *root, int *flag, int *EXT_VAR){
    SymbolNode *node = root;
    word *direct_word = (word *)malloc(sizeof(word));
    while (node->next != NULL){/*search in the symbols table*/
        node = node->next;
        if(!strcmp(argument, node->symbol)){/*arg can only appear once in the table*/
            direct_word->bits = node->value;
            if (node->attribute & 4)
            {
                *EXT_VAR = TRUE;
            }
            return direct_word;
        }
    }
    UNDEFINED_LABEL_ERROR(flag, argument);
    return direct_word;
}

/**
 * create a word by the relative addressing method
 * @param argument
 * @param ic
 * @param root
 * @param EXT_VAR
 * @return a pointer to the word
 */
word *get_word_relative(char *argument, int ic, SymbolNode *root, int *EXT_VAR, int *flag){
    word *relative_word = (word *)malloc(sizeof(word));
    char *label = (char *)malloc(sizeof(char)* MAX_ARGUMENT);
    int label_row;
    strcpy(label, argument);
    label_row = search_symbol_table(label, root, EXT_VAR);
    if (label_row == -1){
        ILLEGAL_LABEL_SYNTAX_ERROR(flag, 0);
    }
    relative_word->bits = label_row - ic;
    return relative_word;
}

/**
 * create a word by the register addressing method
 * @param argument
 * @return
 */
word *get_word_register(char *argument){
    int shift;
    word *register_word = (word *)malloc(sizeof(word));
    register_word->bits += 1;
    shift = argument[1] - '0'; /* convert argument[1] to int */
    register_word->bits = register_word->bits << shift;
    return register_word;
}

/**
 * create word contains the int i
 * @param i
 * @return a pointer to the word
 */
word *get_word(int i) {
    word *w = (word *)malloc(sizeof(word));
    w->bits = i;
    return w;
}

/**
 * get dest of a "first word"
 * @param w
 * @return dest - int
 */
int get_dest(word *w){
    return w->bits & 3;
}

/**
 * get source of a "first word"
 * @param w
 * @return source - int
 */
int get_source(word *w){
    return w->bits & 12;
}

