#ifndef ASSEMBLER_TEXT_PROCESS_H
#define ASSEMBLER_TEXT_PROCESS_H

#include <stdio.h>
#include "assembler_main.h"


int get_line(FILE *file_name, char *line);

int get_first_token(char *line, char *argument);

int get_next_token(char *argument);

void drop_comma(char *str);

void drop_marks(char *str);

word *get_word(int i);

int get_label(char *line, char *label);

int is_directive(char *argument);

void get_command(char *argument, OperationItem *p, OperationItem *table);

int is_comma(char *argument);

int get_first_operand(char *argument, char *operand);

int get_second_operand(char *operand);

int operand_address_method(char *argument);

/* 2 functions bellow need to be writen. only declared */
int is_comment_line(char *line);

int is_empty_line(char *line);


#endif
