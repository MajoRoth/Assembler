#ifndef ASSEMBLER_DATA_STRUCTURES_H
#define ASSEMBLER_DATA_STRUCTURES_H

/**
 * DEFINE DATA STRUCTURES BELLOW
 */
enum {
    NONE = 16, IMMEDIATE = 8, DIRECT = 4,
    RELATIVE = 2, DIRECT_REG = 1, ILLEGAL_TYPE = 0
};

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct TableRow{
    word *w;
    int ARE;
} TableRow;

typedef struct SymbolNode{
    struct SymbolNode *next;
    char *symbol;
    int value;
    int attribute; /* one line can have 2 symbols. for example data and extern */
} SymbolNode;

typedef struct OperationItem{
    char *name;
    int opcode;
    int funct;
    int words_num; /* L */
    int operands[2];/* operands[0] is for the source and operands[1] is for the dest */
} OperationItem;

typedef struct OperationL{
    char *name;
    int words_num; /* L */
} OperationL;

typedef struct External_list_Node{
    struct External_list_Node *next;
    char *symbol;
    int value;
}External_list_Node;

/**
 * searching command and returning her pointer in **p
 * @param argument - char *
 * @param p - the operation that returns
 * @param table - the table head
 */
void get_command(char *argument, OperationItem **p, OperationItem *table);

/**
 * searching command_L and returning her pointer in **p
 * @param argument - char *
 * @param p - the operation_L that returns
 * @param table - the table head
 */
void get_command_L(char *argument, OperationL **p, OperationL *table);

/**
 * initialize a list
 * @return a pointer to the root
 */
SymbolNode *get_symbol_root();

/**
 * adds a node to the linked list
 * @param symbol - char *
 * @param value  - int
 * @param attribute - int
 * @param prev - the node you want to concatenate to
 * @return a pointer to the new node
 */
SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);

/**
 * get the last node from a linked list
 * @param root
 * @return a pointer to the last node
 */
SymbolNode *get_last_node(SymbolNode *root);

/**
 * initialize a list
 * @return a pointer to the root
 */
External_list_Node *get_external_list_root();

/**
 * adds a node to the linked list
 * @param symbol - char *
 * @param value  - int
 * @param attribute - int
 * @param prev - the node you want to concatenate to
 * @return a pointer to the new node
 */
External_list_Node *add_external_list_node(char *symbol, int value, External_list_Node *prev);

/**
 * get the last node from a linked list
 * @param root
 * @return a pointer to the last node
 */
External_list_Node *get_last_external_list_node(External_list_Node *root);

/**
 * check if a node has data attribute
 * @param node
 * @return 1 if true 0 if false
 */
int is_symbol_node_data(SymbolNode *node);

/**
 * searches a label in the symbol table
 * @param label
 * @param root
 * @param EXT_VAR
 * @return the value if it worked -1 if didn't
 */
int search_symbol_table(char *label, SymbolNode *root, int *EXT_VAR);

/**
 * add entry attribute to symbol
 * @param label
 * @return 1 if worked 0 if didn't
 */
int add_entry_to_symbol(char *label);

/**
 * iterates through the symbol list and adds ICF to data labels
 * @param root
 * @param ICF
 */
void add_ic(SymbolNode *root, int ICF);

/**
 * creating the "first word" of each operation
 * @param command
 * @param source
 * @param dest
 * @return a pointer to the word
 */
word *get_first_word(OperationItem *command, int source, int dest);

/**
 * create a word by the immediate addressing method
 * @param argument
 * @return a pointer to the word
 */
word *get_word_immediate(char *argument);

/**
 * create a word by the direct addressing method
 * @param argument
 * @param root
 * @param flag
 * @param EXT_VAR
 * @return a pointer to the word
 */
word *get_word_direct(char *argument, SymbolNode *root, int *flag, int *EXT_VAR);

/**
 * create a word by the relative addressing method
 * @param argument
 * @param ic
 * @param root
 * @param EXT_VAR
 * @return a pointer to the word
 */
word *get_word_relative(char *argument, int ic, SymbolNode *root, int *EXT_VAR, int *flag);

/**
 * create a word by the register addressing method
 * @param argument
 * @return
 */
word *get_word_register(char *argument);

/**
 * create word contains the int i
 * @param i
 * @return a pointer to the word
 */
word *get_word(int i);

/**
 * get dest of a "first word"
 * @param w
 * @return dest - int
 */
int get_dest(word *w);

int get_source(word *w);


#endif 

