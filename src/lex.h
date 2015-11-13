#ifndef _LEX_
#define _LEX_

#define ID_LEN 10
#define RES_WD_NUM 13

#define IDENT 
#define NUMBER 
#define SYM_CONST -1
#define SYM_VAR -2

const char *res_wd[RES_WD_NUM] = {"var", "const", "procedure", "begin", "end",
                                  "odd", "if", "then", "call", "while", "do",
                                  "read", "write"
                                 };

int sym;
char id[ID_LEN];
int num;

char ch = ' ';

void getch();
void getsym();

#endif