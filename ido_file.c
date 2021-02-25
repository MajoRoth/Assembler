/*temporary file*/

word *get_word_relative(char *argument, int ic){
    word *relative_word = (word *)malloc(sizeof(word));
    char *label = (char *)malloc(sizeof(char)* MAX_ARGUMENT);
    int label_row;
    strcpy(label, &argument[1]);
    label_row = search_symbole_table(label);
    if (label_row == -1){
        /*ERROR*/
    }
    relative_word->bits += (label_row - (ic+1));
    return relative_word;
}


int search_symbole_table(char *label, SymbolNode *root){
    /*AMIT - i didnt remember whether this func exists*/
    SymbolNode *node = root;
    while(node->next != NULL){
        node = node->next;
        if (!strcmp(label,node->symbol)){
            return node->value;
        }
    }
    /*if search failed*/
    return -1;
}