#ifndef __PARSER__
#define __PARSER__

#include "lexer.h"

#define TX_MAX 128

typedef enum {
    variable,
    constant,
    procedure
} object;

struct {
    char name[ID_MAX];
    object kind;
    union {
        int level;
        int val;
    } info;
    int addr;
} table[TX_MAX];

void block();

#endif