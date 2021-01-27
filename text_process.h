#ifndef ASSEMBLER_TEXT_PROCESS_H
#define ASSEMBLER_TEXT_PROCESS_H


int *get_line(FILE *file_name, char *line);

int *get_first_token(char *line, char *token);

char *get_next_token(char *token);

void drop_comma(char *str);

void drop_marks(char *str);

word *get_word(int i);

int *get_label(char *line, char *label);

int is_directive(char *argument);

OperationItem get_command(char *argument);

int is_comma(char *argument);

int *get_first_operand(char *argument, char *operand);

char *get_second_operand(char *operand);

int operand_address_method(char *argument);


#endif
