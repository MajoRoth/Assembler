
#include "assembler.h"
char *get_line(FILE *file_name){
    /* takes the next line from the file and returns it. if there is no more lines return '\0'*/
    char line[MAX_LINE];
    int i=0;
    char c;
    while ((c=getc(file_name)) != '\n'){
        if (c == '\0') return '\0';
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
    word *w;
    w->bits = i;
    return w;

}

char *get_label(char *line){
    /* checks for label. if there is label set the flag is_label to true, else to false
     * returns the index which the line resumes*/
    int i;
    char *label;
    for (i=0; i<MAX_LABEL; i++){
        if (line[i] == ':'){
            if((65 <= line[0] && line[0] <= 90) ||(97 <= line[0] && line[0] <= 122)){ /* checks wether c in A-Z or a-z */
                return label; /* need to be check if label already exists in symbol table */
            }
            else{
                printf("ERROR: label %s does not start with a letter", label);/*exit program? */
                return label;
            }
        }
        if ((48 <= line[i] && line[i] <= 57) || (65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122)){
            /* checks wether c in A-Z or a-z  or 0-9*/
            label[i] = line[i];
        }
        else {
            return "\0";
        }
    }
}

int is_directive(char *argument){
    /* checks for label.
     * returns enum attribute {code, string, data, external, entry} or -1*/
    if (!strcmp(argument, '.string')){
        return string;
    }
    else if (!strcmp(argument, '.data')){
        return data;
    }
    else if (!strcmp(argument, '.extern')){
        return external;
    }
    else if (!strcmp(argument, '.entry')){
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
    return hash_table[16];
}