#include "text_process.h"
#include "assembler_main.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_line(FILE *file_name, char *line){
    /* takes the next line from the file and copy it to the flag line.
     return 1 is sucseeded and 0 otherwise*/
    int i=0;
    char c;
    while ((c=getc(file_name)) != '\n'){
        line[i] = c;
        i++;
    }
    return 1;;
}

int get_first_token(char *line, char *argument){
    /*
     * call this function the first time on evey new line - then call the rest of the times get_next_token()
     * line - the output from get_line()
    */
    argument = strtok(line, " ");
    return 1;
}

int get_next_token(char *argument) {
    /*
     * call this function only if you called get_first_token() before!
    */
    argument = strtok(NULL, " ");
    return 1;
}

void drop_comma(char *str) {
    char *src, *dst;
    char del = ',';
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != del) dst++;
    }
    *dst = '\0';
}

void drop_marks(char *str) {
    /* NEED TO BE WRITEN - FUNCTION NOT READY */
    char *src, *dst;
    char del = '\"';
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != del) dst++;
    }
    *dst = '\0';
}



word *get_word(int i) {
    word *w = (word *)malloc(sizeof(word));
    w->bits = i;
    return w;

}

int get_label(char *line, char *label){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns the index which the line resumes*/
    int i;
    label = " ";
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if(isalpha(line[0])){ /* checks if c in A-Z or a-z */
                return 1; /* need to be check if label already exists in symbol table */
            }
            else{
                printf("ERROR: label %s does not start with a letter", label);/*exit program? */
                return 0;
            }
        }
        if (isdigit(line[i]) || isalpha(line[i])){
            /* checks if c in A-Z or a-z  or 0-9*/
            label[i] = line[i];
        }
        else {
            return 0;
        }
    }
    return 0;
}

int is_directive(char *argument){
    /* checks for label.
     * returns enum attribute {code, string, data, external, entry} or -1*/
    if (!strcmp(argument, ".string")){
        return string;
    }
    else if (!strcmp(argument, ".data")){
        return data;
    }
    else if (!strcmp(argument, ".extern")){
        return external;
    }
    else if (!strcmp(argument, ".entry")){
        return entry;
    }
    else{
        return -1;
    }    
}

void get_command(char *argument, OperationItem *p, OperationItem *table){
    /* ignores spaces and returns the next command */
    int i;
    for (i=0; i< 16; i++){
        if (!strcmp(operation_table[i].name, argument)){
            p = table+i;
            return;
        }
    }
    p = table+16;
}

int is_comma(char *argument){
    /*checks wether there is a comma in argument*/
    int i = 0;
    while(argument[i] != '\0'){
        if (argument[i] == ','){
            return 1;
        }
        i++;
    }
    return 0;
}

/* AMIT - MAYBE DO SOMTHING WITH MACRO? - REPETETIVE FUNCTIONS*/
int get_first_operand(char *argument, char *operand) {
    /*
     * call this function the first time on evey new line - 
     * then call the rest of the times get_second_operand()
    */
    operand = strtok(argument, ",");
    return 1;
}

int get_second_operand(char *operand) {
    /*
     * call this function only if you called get_first_operand() before!
    */
    operand = strtok(NULL, ",");
    return 1;
}

int operand_address_method(char *argument){
    /*returns a number between 0-3 that represents the operand address number*/
    if (argument[0] == '#'){
        return 0;
    }
    else if (argument[0] == '%'){
        return 2;
    }
    else if ((argument[0] == 'r') && (argument[1] >= 48 && argument[1] <= 55)){ /*registers: r0-r7 */
        return 3;
    }
    else{
        return 1;
    }
}

int is_comment_line(char *line){
    /* NOT READY YET */
    return 1;
}

int is_empty_line(char *line){
    /* NOT READY YET. */
    return 1;
}
