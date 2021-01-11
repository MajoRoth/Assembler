//
// Created by Amit Roth on 11/01/2021.
//
#include "assembler.h"
char *get_line(){
    /* takes the next line from the file and returns it. if there is no more lines return '\0'*/
    char line[80];
    int i=0
    while ((c=getchar()) != '\n'){
        if (c == '\0') return '\0'
        line[i] = c;
        i++
    }

    return line;
}

char *is_label(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false */
}

int is_directive(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns enum attribute {code, data, external, entry} or -1*/
}

char get_command(){
    /* ignores spaces and returns the next command */
}



