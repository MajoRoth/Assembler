#include "text_process.h"
#include "error_handlers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * parse each line from the file
 * @param file_name
 * @param line
 * @return 1
 */
int get_line(FILE *file_name, char *line){
    int i=0;
    char c;
    while ((c=getc(file_name)) != '\n' && c != -1){
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return 1;
}

/**
 * uses strtok to parse the line
 * must be called first time on each line
 * next arguments parse with get_next_token
 * @param line
 * @param argument
 * @return 1
 */
int get_first_token(char *line, char *argument){
    char *temp;
    temp = strtok(line, " ");
    strcpy(argument, temp);
    return 1;
}

/**
 * uses strtok to parse the line
 * @param argument
 * @return 1 if worked - 0 otherwise
 */
int get_next_token(char *argument) {
    char *temp;
    temp = strtok(NULL, " ");
    if (temp == NULL){
        return 0;
    }
    strcpy(argument, temp);
    return 1;
}

/**
 * remove commas from str
 * @param str
 */
void drop_comma(char *str) {
    char *src, *dst;
    char del = ',';
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != del) dst++;
    }
    *dst = '\0';
}

/**
 * remove marks " from str
 * @param str
 */
void drop_marks(char *str) {
    strcpy(str, &str[3]);
    str[strlen(str)-3] = '\0';
}

/**
 * checks for label in a line
 * @param line
 * @param label
 * @param flag
 * @param line_count
 * @return 1 if worked - 0 otherwise
 */
int get_label(char *line, char *label, int *flag, int line_count){
    int i;
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if(isalpha(line[0])){ /* checks if c in A-Z or a-z */
                label[i] = '\0';
                return 1; /* need to be check if label already exists in symbol table */
            }
            else{
                ILLEGAL_LABEL_SYNTAX_ERROR(flag, line_count);
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

/**
 * checks if a line is directive
 * @param argument
 * @return  enum attribute {code, string, data, external, entry} or -1
 */
int is_directive(char *argument){
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

/**
 * checks wether there is a comma in argument
 * @param argument
 * @return
 */
int is_comma(char *argument){
    int i = 0;
    while(argument[i] != '\0'){
        if (argument[i] == ','){
            return 1;
        }
        i++;
    }
    return 0;
}

/**
 * check addressing method
 * @param argument
 * @return a number between 0-3 that represents the operand address number
 */
int operand_address_method(char *argument){
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

/**
 * use strtok to get the operands
 * like get_first_token use first on each line
 * @param argument
 * @param operand
 * @return
 */
int get_first_operand(char *argument, char *operand) {
    char *temp;
    temp = strtok(argument, ",");
    strcpy(operand, temp);
    return 1;
}

/**
 * use strtok to get the operands
 * @param operand
 * @return
 */
int get_second_operand(char *operand) {
    char *temp;
    temp = strtok(NULL, ",");
    strcpy(operand, temp);
    return 1;
}

/**
 * checks if a line is a comment line
 * @param line
 * @return
 */
int is_comment_line(char *line){
    if (line[0] == ';'){
        return 1;
	}
    else{
        return 0;
    }
}
    
/**
 * checks if a line is an empty line
 * @param line
 * @return
 */
int is_empty_line(char *line){
    int i = 0;
    while(line[i] != '\0' && line[i] != '\n'){
        if(line[i] != ' ' && line[i] != '\t'){
            return 0;
        }
    }
    return 1;
}

