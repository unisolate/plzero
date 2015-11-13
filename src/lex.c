#include "lex.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void getch() {
    ch = getchar();
}

void getsym() {
    while (isspace(ch)) {
        getch();
    }

    if (isalpha(ch)) {
        int id_len = 0;
        while (isalnum(ch)) {
            id[id_len++] = ch;
            getch();
        }
        id[id_len] = '\0';

        for (int i = 0; i < RES_WD_NUM; ++i) {
            if (!strcmp(id, res_wd[i])) {
                sym = sym_table[i];
                return;
            }
        }

        sym = Ident;
    } else if (isdigit(ch)) {
        num = 0;
        while (isdigit(ch)) {
            num = num * 10 + ch - '0';
            getch();
        }

        sym = Number;
    } else if (ch == ',') {
        sym = Comma;
    } else if (ch == '=') {
        sym = Equal;
    } else if (ch == ':') {
        getch();
        if (ch == '=') {
            sym = Assign;
        } else {
            sym = Error;
        }
    } else if (ch == '#') {
        sym = NotEqual;
    } else if (ch == '(') {
        sym = LeftParentheses;
    } else if (ch == ')') {
        sym = RightParentheses;
    } else if (ch == '+') {
        sym = Plus;
    } else if (ch == '-') {
        sym = Minus;
    } else if (ch == '*') {
        sym = Multiply;
    } else if (ch == '/') {
        sym = Divide;
    } else if (ch == '<') {
        sym = Less;
    } else if (ch == '>') {
        sym = Greater;
    } else if (ch == ';') {
        sym = Semicolon;
    }
}