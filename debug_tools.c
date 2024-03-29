#include "debug_tools.h"
#include "assembler_main.h"

/**
 * DEBUG TOOLS - writen to internal use.
 * we decided to keep those functions to experiment with the project in the future.
 * it is nice to see visually what happens "inside"
 */

/**
 * prints a word in binary
 */
void print_word(word *w){
    int i;
    int bits = w->bits;

    for(i=0; i<12; i++){
        if (bits & 2048){
            printf("1");
        }
        else{
            printf("0");
        }
        bits <<=1;
    }
}

/**
 * prints ic
 */
void print_table_row_ic(int i, int j){
    printf("\n---printing ic---\n");
    for(; i<j; i++){
        printf("%d\t", i);
        print_word(command_memory[i].w);
        printf("\t%d\n", command_memory[i].ARE);
    } 
}

/**
 * prints dc
 */
void print_table_row_dc(int i, int j){
    for(; i<j; i++){
        printf("%d\t", i);
        print_word(directive_memory[i].w);
        printf("\t%d\n", directive_memory[i].ARE);
    } 
}

/**
 * prints symbol list
 */
void print_table_symbol(SymbolNode *root){
    SymbolNode *node = root;
    printf("---printing symbol table---\n");
    while(node->next != NULL){
        node = node->next;
        printf("%s\t%d\t%d", node->symbol, node->value, node->attribute);
        printf("\n");
    } 
}

