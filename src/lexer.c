#include "plzero.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void getch() {
    if (charCnt == lineLen) {
        if (feof(srcFile)) {
            printf("      program incomplete\n");
            exit(1);
        }

        lineLen = 0;
        charCnt = 0;
        printf("%5d ", codeAlloIdx);
        while ((!feof(srcFile)) && ((ch = getc(srcFile)) != '\n')) {
            printf("%c", ch);
            ++lineLen;
            line[lineLen] = ch;
        }
        printf("\n");
        ++lineLen;
        line[lineLen] = ' ';
    }
    ++charCnt;
    ch = line[charCnt];
}

void getsym() {
    int len = 0;

    while (ch == ' ' || ch == '\t') {
        getch();
    }
    
    if (isalpha(ch)) {  // identified or reserved
        while (len < ID_LEN && isalnum(ch)) {
            id[len++] = ch;
            getch();
        }
        id[len] = '\0';
        
        while (isalnum(ch)) {
            getch();
        }

        for (int i = 0; i < RES_NUM; ++i) {
            if(!strcmp(id, resWord[i])) {
                sym = wordSym[i];
                return;
            }
        }
        sym = IDENT;
    } else if (isdigit(ch)) {  // number
        num = 0;
        sym = NUMBER;
        
        while (isdigit(ch)) {
            num = num * 10 + ch - '0';
            ++len;
            getch();
        }
        
        if (len > DIGIT_MAX) {
            error(31);
        }
    } else if (ch == ':') {
        getch();
        if (ch == '=') {
            sym = BECOMES;
            getch();
        } else {
            sym = NUL;
        }
    } else if (ch == '<') {
        getch();
        if (ch == '=') {
            sym = LEQ;
            getch();
        } else if (ch == '>') {
            sym = NEQ;
            getch();
        } else {
            sym = LSS;
        }
    } else if (ch == '>') {
        getch();
        if (ch == '=') {
            sym = GEQ;
            getch();
        } else {
            sym = GTR;
        }
    } else {
        sym = wordSym[(unsigned char)ch];
        getch();
    }
}