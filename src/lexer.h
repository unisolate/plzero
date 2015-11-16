#ifndef _LEXER_
#define _LEXER_

#define ID_LEN 10
#define RES_WD_NUM 13
#define SYM_NUM 31

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

    Error,
    Ident,
    Number,
    Assign,
    Greater,
    Less,
    GreaterEqual,
    LessEqual,

    Comma,
    Semicolon,
    LeftParentheses,
    RightParentheses,
    Plus,
    Minus,
    Multiply,
    Divide,
    Equal,
    NotEqual
} symType;

const char *res_wd[RES_WD_NUM] = {"var", "const", "procedure", "begin", "end",
                                  "odd", "if",    "then",      "call",  "while",
                                  "do",  "read",  "write"};

symType sym_table[256] = {Var,  Const, Procedure, Begin, End,  Odd,  If,
                          Then, Call,  While,     Do,    Read, Write};

symType sym;
char id[ID_LEN + 1];
int num;

char ch;

void getch();
void getsym();

#endif