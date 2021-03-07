#ifndef ASSEMBLER_SECOND_STAGE_H
#define ASSEMBLER_SECOND_STAGE_H

#include <stdio.h>

int second_stage(FILE *file, char *file_name);

void create_files(char *file_name);

void create_entry(char *file_name);

void create_external(char *file_name);

#endif


