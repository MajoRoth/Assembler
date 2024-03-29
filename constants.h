#ifndef ASSEMBLER_CONSTANTS_H
#define ASSEMBLER_CONSTANTS_H
/**
 * CONSTANTS USED BY THE PROJECT
 */
#define MAX_LINE 80
#define MAX_ARGUMENT 20
#define MAX_LABEL 31
#define OPT_SIZE 17
#define MAX_TABLE 4096
#define FIRST_IC_ROW 100
#define UNKNOWN_LINE -1

enum attribute {code = 16, data = 8, external = 4, entry = 2, string = 1};
enum boolean {FALSE, TRUE};
enum are {A,R,E};


#endif

