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

int is_label(char *line, char *label){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns the index which the line resumes*/
    int i;
    char *label;
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if((65 <= line[0] && line[0] <= 90) ||(97 <= line[0] && line[0] <= 122)){ /* checks wether c in A-Z or a-z */
                return i; /* need to be check if label already exists in symbol table */
            }
            else{
                printf("ERROR: label {} does not start with a letter", label);
                return i;
            }
        }
        if ((48 <= line[i] && line[i] <= 57) || (65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122)){
            /* checks wether c in A-Z or a-z  or 0-9*/
            label[i] = line[i];
        }
        else if{
            return 0;
        }
    }
}

int is_directive(char *line, int i, int *directive_type){/*enum element is int??? */
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns enum attribute {code, data, external, entry} or -1*/
    char directive;
    /* ignores the spaces */
    while(line[i] == ' ' || line[i] == '\t'){
        i++
    }
    /*checks wether the next "word" is a directive*/
    if (line[i] != '.'){
        directive_type = -1; 
        return i;
    }
    else{
        /*in case there is a directive, finds what it is*/
        i++;
        while(line[i] != ' ' && line[i] != '\t' line[i] != '\0'){
            directive += line[i]

        }


    }
}

char get_command(){
    /* ignores spaces and returns the next command */
}



