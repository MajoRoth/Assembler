#ifndef ASSEMBLER_TEXT_PROCESS_H
#define ASSEMBLER_TEXT_PROCESS_H

char *get_line();

char *get_first_token(char *line);

char *get_next_token();

void drop_comma(char *str);

void drop_marks(char *str);

word *get_word(int i);

char *get_label(char *line);

int is_directive(char *argument);

OperationItem get_command(char *argument, OperationItem table[OPT_SIZE]);

int is_comma(char *argument);

char *get_first_operand(char *argument);

char *get_second_operand();

int operand_address_method(char *argument);


#endif //ASSEMBLER_TEXT_PROCESS_H
