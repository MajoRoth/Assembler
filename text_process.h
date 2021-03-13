#ifndef ASSEMBLER_TEXT_PROCESS_H
#define ASSEMBLER_TEXT_PROCESS_H

#include <stdio.h>
#include "constants.h"

/**
 * parse each line from the file
 * @param file_name
 * @param line
 * @return 1
 */
int get_line(FILE *file_name, char *line);

/**
 * uses strtok to parse the line
 * must be called first time on each line
 * next arguments parse with get_next_token
 * @param line
 * @param argument
 * @return 1
 */
int get_first_token(char *line, char *argument);

/**
 * uses strtok to parse the line
 * @param argument
 * @return 1 if worked - 0 otherwise
 */
int get_next_token(char *argument);

/**
 * remove commas from str
 * @param str
 */
void drop_comma(char *str);

/**
 * remove marks " from str
 * @param str
 */
void drop_marks(char *str);

/**
 * checks for label in a line
 * @param line
 * @param label
 * @param flag
 * @param line_count
 * @return 1 if worked - 0 otherwise
 */
int get_label(char *line, char *label, int *flag, int line_count);

/**
 * checks if a line is directive
 * @param argument
 * @return  enum attribute {code, string, data, external, entry} or -1
 */
int is_directive(char *argument);

/**
 * checks wether there is a comma in argument
 * @param argument
 * @return
 */
int is_comma(char *argument);

/**
 * check addressing method
 * @param argument
 * @return a number between 0-3 that represents the operand address number
 */
int operand_address_method(char *argument);

/**
 * use strtok to get the operands
 * like get_first_token use first on each line
 * @param argument
 * @param operand
 * @return
 */
int get_first_operand(char *argument, char *operand);

/**
 * use strtok to get the operands
 * @param operand
 * @return
 */
int get_second_operand(char *operand);

/**
 * checks if a line is a comment line
 * @param line
 * @return
 */
int is_comment_line(char *line);

/**
 * checks if a line is an empty line
 * @param line
 * @return
 */
int is_empty_line(char *line);


#endif

