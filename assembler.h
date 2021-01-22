#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TABLE 4096
#define MAX_LINE 80
#define MAX_LABEL 31
#define OPT_SIZE 17

typedef struct word{
    unsigned int bits:12;
} word;

typedef struct TableRow{
    word w;
    int ARE;
} TableRow;

typedef struct OperationItem{
    char *name;
    int opcode;
    int funct;
    int words_num; /* L */
    int legal_source[3];
    int legal_dest[3];
} OperationItem;

typedef struct SymbolNode{
    struct SymbolNode *next;
    char *symbol;
    int value;
    int attributes[2]; /* one line can have 2 symbols. for example data and extern */
} SymbolNode;

enum attribute {code, data, external, entry, string};
enum ARE {A, R, E};
enum boolean {FALSE, TRUE};


/* data structures functions */
OperationItem *get_operation_table();
int get_funct_by_name(char *name, struct OperationItem hash_table[]);
int get_opcode_by_name(char *name, struct OperationItem hash_table[]);
SymbolNode *get_symbol_root();
SymbolNode *add_symbol_node(char *symbol, int value, int attribute, SymbolNode *prev);
SymbolNode *get_last_node(SymbolNode *root);

/* text process */
char *get_line();
char *get_first_token(char *line);
char *get_next_token();
void drop_comma(char *str);
void drop_marks(char *str);
word *get_word(int i);
char *get_label(char *line);
int is_directive(char *argument);
OperationItem get_command(char *argument, OperationItem table[OPT_SIZE]);
int is_comma(char *argument);
char *get_first_operand(char *argument);
char *get_second_operand();
int operand_address_method(char *argument);

/* word process */
word *get_first_word(OperationItem *command, int source, int dest);
word *get_word_immediate(char *argument);
word *get_word_direct(char *argument);
word *get_word_relative(char *argument);
word *get_word_register(char *argument);


