#ifndef _PARSER_
#define _PARSER_

#define CODE_MAX   2000   // size of code array
#define TABLE_MAX  100    // length of identifier table
#define LEV_MAX    3      // max depth of block nesting
#define ADDR_MAX   2047   // max address

extern int wordSym[256];

typedef enum {
    Constant,
    Variable,
    Proc
} object;

struct {
    char name[ID_LEN + 1];
    object kind;
    int val;
    int level;
    int addr;
} table[TABLE_MAX + 1];

char mnemonic[8][3 + 1];
int declBegSys, statBegSys, facBegSys;

// the following variables for block
int dataAlloIdx;   // data allocation index
int lev;           // current depth of block nesting
int tableIdx;      // current table index

void gen(fct x, int y, int z);
void test(int s1, int s2, int n);
void enter(object k);
int position(char* id);
void constdeclaration();
void vardeclaration();
void listcode(int initCodeIdx);
void factor(int fsys);
void term(int fsys);
void expression(int fsys);
void condition(int fsys);
void statement(int fsys);
void block(int fsys);

#endif