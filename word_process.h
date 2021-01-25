#ifndef ASSEMBLER_WORD_PROCESS_H
#define ASSEMBLER_WORD_PROCESS_H

word *get_first_word(OperationItem *command, int source, int dest);

word *get_word_immediate(char *argument);

word *get_word_direct(char *argument);

word *get_word_relative(char *argument);

word *get_word_register(char *argument);


#endif /* ASSEMBLER_WORD_PROCESS_H */