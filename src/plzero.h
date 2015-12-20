#ifndef _PLZERO_
#define _PLZERO_

#define ID_LEN     10    // length of identifiers
#define RES_NUM    13    // number of reserved words
#define CODE_MAX   2000  // size of code array

#define NUL        0x1
#define IDENT      0x2
#define NUMBER     0x4
#define PLUS       0x8
#define MINUS      0x10
#define TIMES      0x20
#define SLASH      0x40
#define ODDSYM     0x80
#define EQL        0x100
#define NEQ        0x200
#define LSS        0x400
#define LEQ        0x800
#define GTR        0x1000
#define GEQ        0x2000
#define LPAREN     0x4000
#define RPAREN     0x8000
#define COMMA      0x10000
#define SEMICOLON  0x20000
#define PERIOD     0x40000
#define BECOMES    0x80000
#define BEGINSYM   0x100000
#define ENDSYM     0x200000
#define IFSYM      0x400000
#define THENSYM    0x800000
#define WHILESYM   0x1000000
#define DOSYM      0x2000000
#define CALLSYM    0x4000000
#define CONSTSYM   0x8000000
#define VARSYM     0x10000000
#define PROCSYM    0x20000000
#define READSYM    0x40000000
#define WRITESYM   0x80000000

typedef enum {
    Lit,
    Opr,
    Lod,
    Sto,
    Cal,
    Int,
    Jmp,
    Jpc
} fct;                // functions

typedef struct {
    fct func;         // function code
    int lev;          // level
    int addr;         // displacement address
} instruction;

int  sym;             // last symbol read
int  charCnt;         // character count
int  lineLen;         // line length
int  num;             // last number read
int  codeAlloIdx;     // code allocation index
char id[ID_LEN + 1];  // last identifier read

instruction code[CODE_MAX + 1];

void error(int n);
void getsym();

#endif