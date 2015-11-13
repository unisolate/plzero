#ifndef _LEX_
#define _LEX_

#define ID_LEN 10
#define RES_WD_NUM 13
#define SYM_NUM 28

typedef enum {
    Var,
    Const,
    Procedure,
    Begin,
    End,
    Odd,
    If,
    Then,
    Call,
    While,
    Do,
    Read,
    Write,

    Ident,
    Number,
    Comma,
    Semicolon,
    LeftParentheses,
    RightParentheses,
    Assign,
    Plus,
    Minus,
    Multiply,
    Divide,
    Equal,
    NotEqual,
    Greater,
    Less,
    GreaterEqual,
    LessEqual,
    Error
} symType;

const char *res_wd[RES_WD_NUM] = {"var", "const", "procedure", "begin", "end",
                                  "odd", "if",    "then",      "call",  "while",
                                  "do",  "read",  "write"};

const symType sym_table[RES_WD_NUM] = {Var, Const, Procedure, Begin, End,
                                       Odd, If,    Then,      Call,  While,
                                       Do,  Read,  Write};

symType sym;
char id[ID_LEN + 1];
int num;

char ch;  // = ' ';

void getch();
void getsym();

#endif