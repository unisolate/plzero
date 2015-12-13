#ifndef _LEXER_
#define _LEXER_

#define ID_MAX  10  // max identifier length
#define RES_NUM 13  // number of reserve words
#define SYM_NUM 31  // number of symbols

typedef enum {
    // reserve words
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
    
    // symbols 
    Error,
    Ident,
    Number,
    
    Assign,             // :=
    Greater,            // >
    Less,               // <
    GreaterEqual,       // >=
    LessEqual,          // <=

    Comma,              // ,
    Semicolon,          // ;
    LeftParentheses,    // (
    RightParentheses,   // )
    Plus,               // +
    Minus,              // -
    Multiply,           // *
    Divide,             // /
    Equal,              // =
    NotEqual            // #
} symType;

const char *res_wd[RES_NUM] = {"var", "const", "procedure", "begin", "end",
                               "odd", "if",    "then",      "call",  "while",
                               "do",  "read",  "write"};

// reserve word look-up table
symType sym_table[256] = {Var,  Const, Procedure, Begin, End,  Odd,  If,
                          Then, Call,  While,     Do,    Read, Write};

symType sym;
char id[ID_MAX + 1];
int num;

char ch;

void init();
void getch();
void getsym();

#endif