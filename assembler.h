//
// Created by Amit Roth on 09/01/2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#endif //ASSEMBLER_ASSEMBLER_H

struct {
    unsigned int bits:12;
} typedef word;

struct RamNode{
    word w;
    int ARE;
};

struct OperationItem{
    char *name;
    int opcode;
    int funct;
};

struct SymbolNode{
    char *symbol;
    int value;
    int attributes[2]; // one line can have 2 symbols. for example data and extern
};

enum attribute {code, data, external, entry};
enum ARE {A, R, E};


struct OperationItem *get_operation_table();

