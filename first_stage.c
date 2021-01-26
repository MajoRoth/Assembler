#include "first_stage.h"
#include "assembler_main.h"
#include "data_structures.h"
#include "text_process.h"
#include <stdio.h>
#include <ctype.h>

int assembler (FILE *file){
    /* temp vars - to make assignments */
    char line[80];
    char *label;
    char *temp_s1;
    char *temp_s2;
    char temp_c;
    int temp_i;
    int source;
    int label;
    word *w1, *w2;

    int ICF, DFC;
    int L = 0;
    int directive=data;
    char *argument;
    OperationItem command;
    int is_label = FALSE; /* flag weather the next line has a label */
    int is_direct = FALSE; /* flag weather the next line is a directive line */

    while (strcmp(line, "\0") != 0){
        /* (line = get_line(file_path)) != '\0' */
        argument = get_first_token(line);
        label = get_label(argument);
        if (strcmp(label, "\0") != 0){
            is_label = TRUE;
            argument = get_next_token();
            if ((directive = is_directive(argument)) != -1){
                is_direct = TRUE;
            }
        }
        else if ((directive = is_directive(argument)) != -1){
            is_direct = TRUE;
        }


        if (is_direct==TRUE){
            /* THIS LINE IS A DIRECT LINE */
            if (is_label==TRUE && (directive==data || directive==string)){
                /* deal with attributes array [2] later */
                /* add the line to the symbol table */
                add_symbol_node(label, DC, data, get_last_node(root));
                /* add the command to the data table */

                /* evaluate for cases - if string add each char in different word and finish with \0
                * if str just put the numbers until there is no more numbers */
                if (directive == data){
                    while ((temp_s1=get_next_token()) != NULL){
                        drop_comma(temp_s1);
                        if (atoi(temp_s1) == 0 && !isdigit(*temp_s1)) {
                            /* PRINT ERROR MESSAGE ?? */
                            continue;
                        }
                        temp_i = atoi(temp_s1);
                        directive_memory[DC].w = *get_word(temp_i);
                        DC++;
                    }
                }
                else {
                    temp_s1 = get_next_token();
                    drop_marks(temp_s1);
                    for (temp_i = 0;  temp_s1[temp_i] != '\0' ; temp_i++) {
                        directive_memory[DC].w = *get_word(temp_s1[temp_i]);
                        DC++;
                    }
                    directive_memory[DC].w = *get_word('\0');
                    DC++;
                }
            }
            else if (directive==external){
                add_symbol_node(label, 0, external, get_last_node(root));
            }
            else {
                /* intern - we dont deal with that in the first round */
            }

        }
        else{
            /* THIS LINE IS A INSTRUCTION LINE */
            if (is_label==TRUE){
                /* ADD TO THE SYMBOL TABLE */
                add_symbol_node(label, IC, code, get_last_node(root));
            }
            /* search the operation name (mov, add) int the table */
            command = get_command(get_next_token(), operation_table);
            L = command.words_num;
            if (L == 2){
                argument = get_next_token();
                if (is_comma(argument)){
                    temp_s1 = get_first_operand(argument);
                    temp_s2 = get_second_operand();
                }
                else{
                    temp_s1 = get_next_token();
                    if (is_comma(temp_s1)){
                        drop_comma(temp_s1);
                        temp_s2 = get_next_token();
                    }
                    else{
                        temp_s2 = get_next_token();
                        if(*temp_s2 == ',' && *(temp_s2+1) == '\0'){
                            temp_s2 = get_next_token();
                        }
                        else if (is_comma(temp_s2)){
                            drop_comma(temp_s2);
                        }
                        else{
                            /* print error - no comma */
                        }
                    }
                }
                source = operand_address_method(temp_s1);
                dest = operand_address_method(temp_s2);
                command_memory[IC++] = get_first_word(command, source, dest);
                /* add the words depends on the address method */
                switch (source) {
                    case 0:
                        w1 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w1 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w1 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w1 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w1;
                switch (dest) {
                    case 0:
                        w2 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w2 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w2 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w2 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w2;
            }
            else if (L == 1){
                temp_s1 = get_next_token();
                dest = operand_address_method(temp_s2);
                command_memory[IC] = get_first_word(command, 0, dest);
                /* add the words depends on the address method */
                switch (dest) {
                    case 0:
                        w1 = get_word_immediate(temp_s1);
                        break;
                    case 1:
                        w1 = get_word_direct(temp_s1);
                        break;
                    case 2:
                        w1 = get_word_relative(temp_s1);
                        break;
                    case 3:
                        w1 = get_word_register(temp_s1);
                        break;
                    default:
                        /* ERROR */
                }
                command_memory[IC++] = w1;
            }
            else{
                command_memory[IC++] = get_first_word(command, 0, 0);
            }
        }

        /* reset the variabels */

        strcpy(line, get_line(file_path));

    }
    ICF = IC;
    DCF = DC;

    add_icf(root, ICF);

    return 1;
}

/* ----- SECOND IMPLEMENTATION ----- */

OperationItem hash_table [] ={
        {"mov",  0,  0, {IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"cmp",  1,  0, {IMMEDIATE + DIRECT + DIRECT_REG, IMMEDIATE + DIRECT + DIRECT_REG}},
        {"add",  2,  1, {IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"sub",  2,  2, {IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"lea",  4,  0, {DIRECT,                          DIRECT + DIRECT_REG}},
        {"clr",  5,  1, {NONE,                            DIRECT + DIRECT_REG}},
        {"not",  5,  2, {NONE,                            DIRECT + DIRECT_REG}},
        {"inc",  5,  3, {NONE,                            DIRECT + DIRECT_REG}},
        {"dec",  5,  4, {NONE,                            DIRECT + DIRECT_REG}},
        {"jmp",  9,  1, {NONE,                            DIRECT + RELATIVE}},
        {"bne",  9,  2, {NONE,                            DIRECT + RELATIVE}},
        {"jsr",  9,  3, {NONE,                            DIRECT + RELATIVE}},
        {"red",  12, 0, {NONE,                            DIRECT + DIRECT_REG}},
        {"prn",  13, 0, {NONE,                            IMMEDIATE + DIRECT + DIRECT_REG}},
        {"rts",  14, 0, {NONE,                            NONE}},
        {"stop", 15, 0, {NONE,                            NONE}},
        {"null",  0, 0, {NONE,                            NONE}}
};

int first_stage(FILE *file){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    enum boolean IS_LABEL = FALSE, ERROR = FALSE, IS_DIRECT = FALSE;
    int directive_type = data;
    int L;
    OperationItem command;

    while (!feof(file))
    {
        /* main loop of stage 1 */
        get_line(file, line);
        if (!is_comment_line(line) && !is_empty_line(line)){
            get_first_token(line, argument);
            if (get_label(line, label)==1){
                IS_LABEL = TRUE;
                get_next_token(argument);
                if ((directive_type = is_directive(argument)) != -1){
                    IS_DIRECT = TRUE;
                }
            }
            else if ((directive_type = is_directive(argument)) != -1){
                IS_DIRECT = TRUE;
            }
        }

        if (IS_DIRECT == TRUE){
            if (IS_LABEL == TRUE && directive_type == data ){
                add_symbol_node(label, DC, data, get_last_node(root));
                directive_data_line();
            }
            else if (IS_LABEL == TRUE && directive_type == string ){
                add_symbol_node(label, DC, data, get_last_node(root));
                directive_string_line()
            }
            else if (directive_type == external){
                add_symbol_node(label, 0, external, get_last_node(root));
            }
            else{
                /* intern line - ignore */
            }
        }
        else{
            if (IS_LABEL == TRUE){
                add_symbol_node(label, IC, code, get_last_node(root));
            }
            get_next_token(argument);
            get_command(argument, command);
            switch (L) {
                case 2:
                    break;
                case 1:
                    break;
                case 0:
                    break;
            }
        }
    }
    add_icf(root, ICF);

}


/*
 *  adds to directive_memory[] the following words of data expression
 */
void directive_data_line(){
    char arg[MAX_ARGUMENT];
    int num;
    while (get_next_token(arg)){
        drop_comma(arg);
        if (atoi(arg) == 0 && !isdigit(*arg)){
            /* not a number */
            continue;
        }
        num = atoi(arg);
        directive_memory[DC++].w = *get_word(num);
    }
}

/*
 *  adds to directive_memory[] the following words of string expression
 */
void directive_string_line(){
    char arg[MAX_ARGUMENT];
    int i;
    get_next_token(arg);
    drop_marks(arg);
    for (i=0; arg[i] != '\0'; i++){
        directive_memory[DC++].w = *get_word(arg[i]);
    }
    directive_memory[DC++].w = *get_word('\0');
}

