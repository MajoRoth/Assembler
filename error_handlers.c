#include "error_handlers.h"
#include "data_structures.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * COMMA ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void COMMA_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL USE OF COMMAS\n", line);
}

/**
 * NAME ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void NAME_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: ILLEGAL NAME OF VARIABLE\n", line);
}

/**
 * DOUBLE DECLARATION ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void DOUBLE_DECLARATION_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: LABEL CAN BE DECLARED ONLY ONCE\n", line);
}

/**
 * LABEL LENGTH ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void LABEL_LENGTH_ERROR(int *flag, int line){
    *flag = TRUE;
    printf("error in line %d: LABEL IS TOO LONG\n", line);
}

/**
 * ILLEGAL LABEL SYNTAX ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void ILLEGAL_LABEL_SYNTAX_ERROR(int *flag, int line){
    *flag = FALSE;
    if (line == UNKNOWN_LINE){
        printf("ILLEGAL LABEL SYNTAX\n");
    }
    else{
        printf("error in line %d: ILLEGAL LABEL SYNTAX\n", line);
    }
}

/**
 * COMMAND ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void COMMAND_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: COMMAND DOES NOT EXISTS\n", line);
}

/**
 * LEGAL OPERANDS ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void LEGAL_OPERANDS_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: ILLEGAL OPERAND FOR THIS COMMAND\n", line);
}

/**
 * OPERANDS NUMBER ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void OPERANDS_NUMBER_ERORR_1(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: TOO MANY OPERANDS\n", line);
}

/**
 * OPERANDS NUMBER ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void OPERANDS_NUMBER_ERORR_2(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: NOT ENOUGH OPERANDS\n", line);
}

/**
 * REGISTER NAME ERROR
 * @param flag - a pointer to error flag
 * @param line - current line for printing
 */
void REGISTER_NAME_ERROR(int *flag, int line){
    *flag = TRUE; 
    printf("error in line %d: ILLEGAL REGISTER NAME\n", line);
}

/**
 * UNDEFINED LABEL ERROR
 * @param flag - a pointer to error flag
 * @param label - the label
 */
void UNDEFINED_LABEL_ERROR(int *flag, char *label){
    *flag = TRUE;
    printf("UNDEFINED LABEL %s\n", label);
}

/**
 * NAME ERROR
 * @param file_name - the name of the invalid file
 */
void FILE_NAME_ERROR(char *file_name){
    printf("ERROR %s invalid file name\n", file_name);
}
