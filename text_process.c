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
                printf("ERROR: label {} does not start with a letter", label);/*exit program? */
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
            if (line[i] < 97 || line[i] > 122){/*directive only include small letters*/
                printf("ERROR: directive is not valid");/*exit the program??*/
                directive_type = -1;
                return i;
            }
            else{
                directive += line[i];
                }
                
            }
            switch (directive){
            case 'string':
                directive_type = string;
                break;
            case 'data':
                directive_type = data;
                break;
            
            case 'extern':
                directive_type = external;
                break;
            
            case 'entry':
                directive_type = entry;
                break;
            
            default:
                directive_type = -1;
                break;
            }

            return i;

        }


    }
}

char get_command(char *line, int i, int *command_type){
    /* ignores spaces and returns the next command */
    char command;
    while(line[i] == ' ' || line[i] == '\t'){
        i++
    }
    while(line[i] != ' ' && line[i] != '\t' line[i] != '\0'){
            if (line[i] < 97 || line[i] > 122){/*commands only include small letters*/
                printf("ERROR: command is not valid");/*exit the program??*/
                command_type = -1;
                return i;
            }
            else{
                command += line[i];
            }
    }
}




