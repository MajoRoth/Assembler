#include "first_stage.h"
#include "assembler_main.h"
#include "data_structures.h"
#include "text_process.h"
#include "word_process.h"
#include <stdio.h>
#include <ctype.h>


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
                    add_instruction_words_2();
                    break;
                case 1:
                    add_instruction_word_1();
                    break;
                case 0:
                    command_memory[IC++] = get_first_word(command, 0, 0);
                    break;
            }
        }
    }
    add_ic(root, IC);
    if (ERROR == FALSE)
        return 1;
    else
        return 0

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

/*
 * adds to IC the words for 2 words instruction
 */
void add_instruction_words_2(){
    char argument[MAX_ARGUMENT];
    char temp1[MAX_ARGUMENT], temp2[MAX_ARGUMENT];
    get_next_token(argument);
    if (is_comma(argument)){
        get_first_operand(argument, temp1);
        get_second_operand(temp2);
    }
    else {
        get_next_token(temp1);
        if (is_comma(temp1)) {
            drop_comma(temp1);
            get_next_token(temp2);
        } else {
            get_next_token(temp2);
            if (*temp2 == ',' && *(temp2 + 1) == '\0') {
                get_next_token(temp2);
            } else if (is_comma(temp_s2)) {
                drop_comma(temp2);
            } else {
                /* print error - no comma */
            }
        }
    }
    source = operand_address_method(temp1);
    dest = operand_address_method(temp2);
    command_memory[IC++] = get_first_word(command, source, dest);

    switch (source) {
        case 0:
            w1 = get_word_immediate(temp1);
            break;
        case 1:
            w1 = get_word_direct(temp1);
            break;
        case 2:
            w1 = get_word_relative(temp1);
            break;
        case 3:
            w1 = get_word_register(temp1);
            break;
        default:
            /* ERROR */
    }
    command_memory[IC++] = w1;
    switch (dest) {
        case 0:
            w2 = get_word_immediate(temp2);
            break;
        case 1:
            w2 = get_word_direct(temp2);
            break;
        case 2:
            w2 = get_word_relative(temp2);
            break;
        case 3:
            w2 = get_word_register(temp2);
            break;
        default:
            /* ERROR */
    }
    command_memory[IC++] = w2;
}

/*
 * adds to IC the a word for 1 word instruction
 */
void add_instruction_word_1(){
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
