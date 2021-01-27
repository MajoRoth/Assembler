#include "text_process.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *get_line(FILE *file_name){
    /* takes the next line from the file and returns it. if there is no more lines return '\0'*/
    char *line = (char *)malloc(MAX_LINE * sizeof (char));
    int i=0;
    char c;
    while ((c=getc(file_name)) != '\n'){
        if (c == '\0') return "\0";
        line[i] = c;
        i++;
    }

    return line;
}

char *get_first_token(char *line) {
    /*
     * call this function the first time on evey new line - then call the rest of the times get_next_token()
     * line - the output from get_line()
    */
    char *token;
    token = strtok(line, " ");
    return token;
}

char *get_next_token() {
    /*
     * call this function only if you called get_first_token() before!
    */
    char *token;
    token = strtok(NULL, " ");
    return token;
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

char *get_label(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns the index which the line resumes*/
    int i;
    char *label = (char *);
    label = " ";
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if(isalpha(line[0])){ /* checks if c in A-Z or a-z */
                return label; /* need to be check if label already exists in symbol table */
            }
            else{
                printf("ERROR: label %s does not start with a letter", label);/*exit program? */
                return label;
            }
        }
        if ((isdigit(line[i]) || isalpha(line[i])){
            /* checks if c in A-Z or a-z  or 0-9*/
            label[i] = line[i];
        }
        else {
            return "\0";
        }
    }
    return "\0";
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

OperationItem get_command(char *argument, OperationItem table[]){
    /* ignores spaces and returns the next command */
    int i;
    for (i=0; i< 16; i++){
        if (!strcmp(table[i].name, argument)){
            return table[i];
        }
    }
    return table[16];
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
char *get_first_operand(char *argument) {
    /*
     * call this function the first time on evey new line - 
     * then call the rest of the times get_second_operand()
    */
    char *operand;
    operand = strtok(argument, ",");
    return operand;
}

char *get_second_operand() {
    /*
     * call this function only if you called get_first_operand() before!
    */
    char *token;
    token = strtok(NULL, ",");
    return token;
}

int operand_address_method(char *argument){
    /*returns a number between 0-3 that represents the operand address number*/
    if (argument[0] == '#'){
        return 0;
    }
    else if (argument[0] == '%'){
        return 2;
    }
    else if (argument[0] == 'r') && (argument[1] >= 48 && argument[1] <= 55){ /*registers: r0-r7 */
        return 3;
    }
    else{
        return 1;
    }
}

FILE open_file(char *filename){
    FILE *file = fopen(filename,"r");
    if(!file){
        printf("file name is not valid");
        exit(0);
    }
    return file;
}