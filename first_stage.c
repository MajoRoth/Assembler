#include "first_stage.h"
#include "assembler_main.h"
#include "data_structures.h"
#include "text_process.h"
#include "constants.h"
#include "debug_tools.h"
#include "error_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* ----- SECOND IMPLEMENTATION ----- */

OperationItem hash_table [] ={
        {"mov",  0,  0, 2,{IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"cmp",  1,  0, 2,{IMMEDIATE + DIRECT + DIRECT_REG, IMMEDIATE + DIRECT + DIRECT_REG}},
        {"add",  2,  10, 2,{IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"sub",  2,  11, 2,{IMMEDIATE + DIRECT + DIRECT_REG, DIRECT + DIRECT_REG}},
        {"lea",  4,  0, 2,{DIRECT,                          DIRECT + DIRECT_REG}},
        {"clr",  5,  10, 1,{NONE,                            DIRECT + DIRECT_REG}},
        {"not",  5,  11, 1,{NONE,                            DIRECT + DIRECT_REG}},
        {"inc",  5,  12, 1,{NONE,                            DIRECT + DIRECT_REG}},
        {"dec",  5,  13, 1,{NONE,                            DIRECT + DIRECT_REG}},
        {"jmp",  9,  10, 1,{NONE,                            DIRECT + RELATIVE}},
        {"bne",  9,  11, 1,{NONE,                            DIRECT + RELATIVE}},
        {"jsr",  9,  12, 1,{NONE,                            DIRECT + RELATIVE}},
        {"red",  12, 0, 1,{NONE,                            DIRECT + DIRECT_REG}},
        {"prn",  13, 0, 1,{NONE,                            IMMEDIATE + DIRECT + DIRECT_REG}},
        {"rts",  14, 0, 0,{NONE,                            NONE}},
        {"stop", 15, 0, 0,{NONE,                            NONE}},
        {"null",  0, 0, 0,{NONE,                            NONE}}
};
enum boolean IS_ERROR = FALSE;

int first_stage(FILE *file){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    enum boolean IS_LABEL = FALSE, IS_DIRECT = FALSE;
    int directive_type = data;
    int L=0;
    enum boolean skip = FALSE;
    OperationItem *command = &hash_table[16]; /*NULL*/

    while (!feof(file))
    {
        /* main loop of stage 1 */
        get_line(file, line);
        printf("[%d] - current line: %s\n", IC, line);
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
        else{
            skip = TRUE;
        }


        if (IS_DIRECT == TRUE && skip == FALSE){
            if (IS_LABEL == TRUE && directive_type == data ){
                add_symbol_node(label, DC, data, get_last_node(root));
                directive_data_line();
            }
            else if (IS_LABEL == TRUE && directive_type == string ){
                add_symbol_node(label, DC, data, get_last_node(root));
                directive_string_line();
            }
            else if (directive_type == external){
                get_next_token(label);
                add_symbol_node(label, 0, external, get_last_node(root));
            }
            else{
                /* intern line - ignore */
            }
        }
        else if (skip == FALSE){
            if (IS_LABEL == TRUE) {
                add_symbol_node(label, IC, code, get_last_node(root));
            }
            get_command(argument, &command, hash_table);
            L = command->words_num;
            printf("L: %d name: %s", L, command->name);
            switch (L) {
                case 2:
                    add_instruction_words_2(command);
                    break;
                case 1:
                    add_instruction_word_1(command);
                    break;
                case 0:
                    command_memory[IC++].w = get_first_word(command, 0, 0);
                    break;
            }
        }
        free_temp(line, argument, label);
        IS_LABEL = FALSE;
        IS_DIRECT = FALSE;
        skip = FALSE;
    }
    add_ic(root, IC);
    print_table_symbol(root);
    if (IS_ERROR == TRUE)
        return 0;
    else
        return 1;
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
        directive_memory[DC++].w = get_word(num);
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
        directive_memory[DC++].w = get_word(arg[i]);
    }
    directive_memory[DC++].w = get_word('\0');
}

/*
 * adds to IC the words for 2 words instruction
 */
void add_instruction_words_2(OperationItem *command){
    char argument[MAX_ARGUMENT];
    char *temp1 = (char *)malloc(MAX_ARGUMENT * sizeof(char));
    char *temp2 = (char *)malloc(MAX_ARGUMENT * sizeof(char));
    word *w1 = 0, *w2 = 0;
    int source, dest; 
    get_next_token(argument);
    /* AMIT - FIX UNTILL NEXT MEETING, NEED TO WORK AT ALL WAYS WITH COMMAS AND SPACES */
    if (is_comma(argument)){
        if(!get_next_token(temp2)){
            get_first_operand(argument, temp1);
            get_second_operand(temp2);
        }
        else{
            drop_comma(argument);
            strcpy(temp1, argument);
        }
    }
    else {
        strcpy(temp1, argument);
        get_next_token(temp2);
        if(temp2[0] == ',' && temp2[1] == '\0'){
            get_next_token(temp2);
        }
        else if(is_comma(temp2)){
            drop_comma(temp2);
        }
        else{
            COMMA_ERROR(&IS_ERROR, 0);
        }

    }
    source = operand_address_method(temp1);
    dest = operand_address_method(temp2);
    /* YOU HAVE DEST, SOURCE AND COMMAND */
    /* CHECK_OPERANDS(IS_ERROR, line_number, source, dest, command)*/
    command_memory[IC++].w = get_first_word(command, source, dest);
    printf("CM %d ", IC-1);
    print_word(command_memory[IC-1].w);
    switch (source) {
        case 0:
            w1 = get_word_immediate(temp1);
            break;
        case 1:
            w1 = 0; /* done at second stage */
            break;
        case 2:
            w1 = 0; /* done at second stage */
            break;
        case 3:
            w1 = get_word_register(temp1);
            break;
        default:
            w1 = 0; /* ERROR */
    }
    command_memory[IC++].w = w1;
    switch (dest) {
        case 0:
            w2 = get_word_immediate(temp2);
            break;
        case 1:
            w2 = 0; /* done at second stage */
            break;
        case 2:
            w2 = 0; /* done at second stage */
            break;
        case 3:
            w2 = get_word_register(temp2);
            break;
        default:
            w2 = 0; /* ERROR */
    }
    command_memory[IC++].w = w2;
}

/*
 * adds to IC the a word for 1 word instruction
 */
void add_instruction_word_1(OperationItem *command){
    char argument[MAX_ARGUMENT];
    int dest;
    word *w1 = 0;
    get_next_token(argument);
    dest = operand_address_method(argument);
    command_memory[IC++].w = get_first_word(command, 0, dest);
    printf("CM %d ", IC-1);
    print_word(command_memory[IC-1].w);
    /* add the words depends on the address method */
    switch (dest) {
        case 0:
            w1 = get_word_immediate(argument);
            break;
        case 1:
            w1 = 0; /* done at second stage */
            break;
        case 2:
            w1 = 0; /* done at second stage */
            break;
        case 3:
            w1 = get_word_register(argument);
            break;
        default:
            printf("ERROR");
            /* ERROR */
    }
    command_memory[IC++].w = w1;
}

void free_temp(char *line, char *argument, char *label){
    memset(line, 0, MAX_LINE);
    memset(argument, 0, MAX_ARGUMENT);
    memset(label, 0, MAX_LABEL);
}



/*int assembler (FILE *file){
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
    int is_label = FALSE;
    int is_direct = FALSE;

    while (strcmp(line, "\0") != 0){
         (line = get_line(file_path)) != '\0'
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

            if (is_label==TRUE && (directive==data || directive==string)){
                add_symbol_node(label, DC, data, get_last_node(root));

                if (directive == data){
                    while ((temp_s1=get_next_token()) != NULL){
                        drop_comma(temp_s1);
                        if (atoi(temp_s1) == 0 && !isdigit(*temp_s1)) {

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
            }

        }
        else{

            if (is_label==TRUE){

                add_symbol_node(label, IC, code, get_last_node(root));
            }

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

                        }
                    }
                }
                source = operand_address_method(temp_s1);
                dest = operand_address_method(temp_s2);
                command_memory[IC++] = get_first_word(command, source, dest);

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

                }
                command_memory[IC++] = w2;
            }
            else if (L == 1){
                temp_s1 = get_next_token();
                dest = operand_address_method(temp_s2);
                command_memory[IC] = get_first_word(command, 0, dest);
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
                }
                command_memory[IC++] = w1;
            }
            else{
                command_memory[IC++] = get_first_word(command, 0, 0);
            }
        }


        strcpy(line, get_line(file_path));

    }
    ICF = IC;
    DCF = DC;

    add_ic(root, ICF);

    return 1;
}
*/
