#include "debug_tools.h"

void print_word(word w){
    int i;
    for(i=0; i<12; i++){
        if (w.bits & 2048){
            printf("1");
        }
        else{
            printf("0");
        }
        w.bits <<=1;
    }
    printf("\n");
}

void print_table_row(TableRow t){
    print_word(t.w);
    printf("\t%d\n", &t.ARE);
}


void print_table_symbol(SymbolNode *root){
    /* print all nodes until node->next == null */
    SymbolNode *node = root;
    while(node->next != null){
        printf("%s\t%d\t%d", &node->symbol, &node->value, &node->attributes[0]);
        if(!(node->attributes[1])){/*checks wether there is second attribute*/
            printf(",%d",&node->attributes[1]);
        }
        printf("\n");
        node = node->next;
    } 
}
