#ifndef ASSEMBLER_TEXT_PROCESS_H
#define ASSEMBLER_TEXT_PROCESS_H

#include <stdio.h>
#include "constants.h"


int get_line(FILE *file_name, char *line);

int get_first_token(char *line, char *argument);

int get_next_token(char *argument);

void drop_comma(char *str);

void drop_marks(char *str);

int get_label(char *line, char *label, int *flag, int line_count);

int is_directive(char *argument);

int is_comma(char *argument);

int operand_address_method(char *argument);

/* AMIT - MAYBE DO SOMTHING WITH MACRO? - REPETETIVE FUNCTIONS*/
int get_first_operand(char *argument, char *operand);

int get_second_operand(char *operand);


int is_comment_line(char *line);

int is_empty_line(char *line);


#endif
