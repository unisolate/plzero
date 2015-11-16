#include "lexer.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void init() {
    sym_table[','] = Comma;
    sym_table['='] = Equal;
    sym_table['#'] = NotEqual;
    sym_table['('] = LeftParentheses;
    sym_table[')'] = RightParentheses;
    sym_table['+'] = Plus;
    sym_table['-'] = Minus;
    sym_table['*'] = Multiply;
    sym_table['/'] = Divide;
    sym_table[';'] = Semicolon;

    ch = ' ';
}

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
    } else if (ch == ':') {
        getch();
        if (ch == '=') {
            sym = Assign;
            getch();
        } else {
            sym = Error;
        }
    } else if (ch == '<') {
        getch();
        if (ch == '=') {
            sym = LessEqual;
            getch();
        } else {
            sym = Less;
        }
    } else if (ch == '>') {
        getch();
        if (ch == '=') {
            sym = GreaterEqual;
            getch();
        } else {
            sym = Greater;
        }
    } else {
        sym = sym_table[ch];
        getch();
    }
}