//
// Created by Amit Roth on 11/01/2021.
//
#include "assembler.h"
char *get_line(FILE *file_name){
    /* takes the next line from the file and returns it. if there is no more lines return '\0'*/
    char line[MAX_LINE];
    int i=0
    while ((c=getc(file_name)) != '\n'){
        if (c == '\0') return '\0'
        line[i] = c;
        i++
    }

    return line;
}

char *is_label(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false */
    int i;
    char *label;
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if((65 <= line[0] && line[0] <= 90) ||(97 <= line[0] && line[0] <= 122)){ /* check weather c in A-Z or a-z */
                return label; /* need to be check if label already exists in symbol table */
            }
            else{
                printf("ERROR: label {} does not start with a letter", label);
                return '\0';
            }
        }
        if ((48 <= line[i] && line[i] <= 57) || (65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122)){
            /* check weather c in A-Z or a-z  or 0-9*/
            label[i] = line[i];
        }
        else if{
            return '\0';
        }
    }
}

int is_directive(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns enum attribute {code, data, external, entry} or -1*/
}

char get_command(){
    /* ignores spaces and returns the next command */
}



