#ifndef _LEXER_
#define _LEXER_

#include <stdio.h>

#define DIGIT_MAX 14    // max number of digits in numbers

extern char *resWord[RES_NUM];
extern int wordSym[256];

int err;
char ch;                // last character read
char line[81];
FILE* srcFile;

void getch();

#endif