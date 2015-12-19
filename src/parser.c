#include "plzero.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void gen(fct x, int y, int z) {
    if (codeAlloIdx > CODE_MAX) {
        printf("program too long\n");
        exit(1);
    }
    code[codeAlloIdx].func = x;
    code[codeAlloIdx].lev = y;
    code[codeAlloIdx].addr = z;
    ++codeAlloIdx;
}

void test(int s1, int s2, int n) {
    if (!(sym & s1)) {
        error(n);
        s1 = s1 | s2;
        while (!(sym & s1)) {
            getsym();
        }
    }
}

void enter(object k) {  // enter object into table
    ++tableIdx;
    strcpy(table[tableIdx].name, id);
    table[tableIdx].kind = k;
    
    switch (k) {
        case Constant:
            if (num > ADDR_MAX) {
                error(31);
                num = 0;
            }
            table[tableIdx].val = num;
            break;
        case Variable:
            table[tableIdx].level = lev;
            table[tableIdx].addr = dataAlloIdx;
            ++dataAlloIdx;
            break;
        case Proc:
            table[tableIdx].level = lev;
            break;
    }
}

int position(char* id) {  // find identifier id in table
    int i;

    strcpy(table[0].name, id);
    i = tableIdx;
    while (strcmp(table[i].name, id) != 0) {
        i = i - 1;
    }
    return i;
}

void constdeclaration() {
    if (sym == IDENT) {
        getsym();
        if (sym == EQL || sym == BECOMES) {
            if (sym == BECOMES) {
                error(1);
            }
            getsym();
            if (sym == NUMBER) {
                enter(Constant);
                getsym();
            } else {
                error(2);
            }
        } else {
            error(3);
        }
    } else {
        error(4);
    }
}

void vardeclaration() {
    if (sym == IDENT) {
        enter(Variable);
        getsym();
    } else {
        error(4);
    }
}

void listcode(int initCodeIdx) {  // list code generated for this block
    int i;

    for (i = initCodeIdx; i <= codeAlloIdx - 1; i++) {
        printf("%10d%5s%3d%5d\n", i, mnemonic[code[i].func], code[i].lev, code[i].addr);
    }
}

void factor(int fsys) {
    int i;

    test(facBegSys, fsys, 24);
    while (sym & facBegSys) {
        if (sym == IDENT) {
            i = position(id);
            if (i == 0) {
                error(11);
            } else {
                switch (table[i].kind) {
                    case Constant:
                        gen(Lit, 0, table[i].val);
                        break;
                    case Variable:
                        gen(Lod, lev - table[i].level, table[i].addr);
                        break;
                    case Proc:
                        error(21);
                        break;
                }
            }
            getsym();
        } else if (sym == NUMBER) {
            if (num > ADDR_MAX) {
                error(31);
                num = 0;
            }
            gen(Lit, 0, num);
            getsym();
        } else if (sym == LPAREN) {
            getsym();
            expression(RPAREN | fsys);
            if (sym == RPAREN) {
                getsym();
            } else {
                error(22);
            }
        }
        test(fsys, LPAREN, 23);
    }
}

void term(int fsys) {
    int mulop;

    factor(fsys | TIMES | SLASH);
    while (sym == TIMES || sym == SLASH) {
        mulop = sym;
        getsym();
        factor(fsys | TIMES | SLASH);
        if (mulop == TIMES) {
            gen(Opr, 0, 4);
        } else {
            gen(Opr, 0, 5);
        }
    }
}

void expression(int fsys) {
    int addop;

    if (sym == PLUS || sym == MINUS) {
        addop = sym;
        getsym();
        term(fsys | PLUS | MINUS);
        if (addop == MINUS) {
            gen(Opr, 0, 1);
        }
    } else {
        term(fsys | PLUS | MINUS);
    }
    while (sym == PLUS || sym == MINUS) {
        addop = sym;
        getsym();
        term(fsys | PLUS | MINUS);
        if (addop == PLUS) {
            gen(Opr, 0, 2);
        } else {
            gen(Opr, 0, 3);
        }
    }
}

void condition(int fsys) {
    int relop;

    if (sym == ODDSYM) {
        getsym();
        expression(fsys);
        gen(Opr, 0, 6);
    } else {
        expression(fsys | EQL | NEQ | LSS | GTR | LEQ | GEQ);
        if (!(sym & (EQL | NEQ | LSS | GTR | LEQ | GEQ))) {
            error(20);
        } else {
            relop = sym;
            getsym();
            expression(fsys);
            switch (relop) {
                case EQL:
                    gen(Opr, 0, 8);
                    break;
                case NEQ:
                    gen(Opr, 0, 9);
                    break;
                case LSS:
                    gen(Opr, 0, 10);
                    break;
                case GEQ:
                    gen(Opr, 0, 11);
                    break;
                case GTR:
                    gen(Opr, 0, 12);
                    break;
                case LEQ:
                    gen(Opr, 0, 13);
                    break;
            }
        }
    }
}

void statement(int fsys) {
    int i, cx1, cx2;

    if (sym == IDENT) {
        i = position(id);
        if (i == 0) {
            error(11);
        } else if (table[i].kind != Variable) {  // assignment to non-Variable
            error(12);
            i = 0;
        }
        getsym();
        if (sym == BECOMES) {
            getsym();
        } else {
            error(13);
        }
        expression(fsys);
        if (i != 0) {
            gen(Sto, lev - table[i].level, table[i].addr);
        }
    } else if (sym == CALLSYM) {
        getsym();
        if (sym != IDENT) {
            error(14);
        } else {
            i = position(id);
            if (i == 0) {
                error(11);
            } else if (table[i].kind == Proc) {
                gen(Cal, lev - table[i].level, table[i].addr);
            } else {
                error(15);
            }
            getsym();
        }
    } else if (sym == IFSYM) {
        getsym();
        condition(fsys | THENSYM | DOSYM);
        if (sym == THENSYM) {
            getsym();
        } else {
            error(16);
        }
        cx1 = codeAlloIdx;
        gen(Jpc, 0, 0);
        statement(fsys);
        code[cx1].addr = codeAlloIdx;
    } else if (sym == BEGINSYM) {
        getsym();
        statement(fsys | SEMICOLON | ENDSYM);
        while (sym == SEMICOLON || (sym & statBegSys)) {
            if (sym == SEMICOLON) {
                getsym();
            } else {
                error(10);
            }
            statement(fsys | SEMICOLON | ENDSYM);
        }
        if (sym == ENDSYM) {
            getsym();
        } else {
            error(17);
        }
    } else if (sym == WHILESYM) {
        cx1 = codeAlloIdx;
        getsym();
        condition(fsys | DOSYM);
        cx2 = codeAlloIdx;
        gen(Jpc, 0, 0);
        if (sym == DOSYM) {
            getsym();
        } else {
            error(18);
        }
        statement(fsys);
        gen(Jmp, 0, cx1);
        code[cx2].addr = codeAlloIdx;
    }
    test(fsys, 0, 19);
}

void block(int fsys) {
    int initTableIdx;    // initial table index
    int initCodeIdx;     // initial code index
    int curTableIdx;     // save current table index
                         // before processing nested procedures
    int curDataAlloIdx;  // save data allocation index

    dataAlloIdx          = 3;
    initTableIdx         = tableIdx;
    table[tableIdx].addr = codeAlloIdx;
    
    gen(Jmp, 0, 0);
    
    if (lev > LEV_MAX) {
        error(32);
    }
    
    do {
        if (sym == CONSTSYM) {
            getsym();
            do {
                constdeclaration();

                while (sym == COMMA) {
                    getsym();
                    constdeclaration();
                }
                
                if (sym == SEMICOLON) {
                    getsym();
                } else {
                    error(5);
                }
            } while (sym == IDENT);
        }
        
        if (sym == VARSYM) {
            getsym();

            do {
                vardeclaration();
                
                while (sym == COMMA) {
                    getsym();
                    vardeclaration();
                }
                
                if (sym == SEMICOLON) {
                    getsym();
                } else {
                    error(5);
                }
            } while (sym == IDENT);
        }
        
        while (sym == PROCSYM) {
            getsym();
            
            if (sym == IDENT) {
                enter(Proc);
                getsym();
            } else {
                error(4);
            }
            
            if (sym == SEMICOLON) {
                getsym();
            } else {
                error(5);
            }
            
            ++lev;
            curTableIdx    = tableIdx;
            curDataAlloIdx = dataAlloIdx;
            
            block(fsys | SEMICOLON);
            
            lev         = lev - 1;
            tableIdx    = curTableIdx;
            dataAlloIdx = curDataAlloIdx;
            
            if (sym == SEMICOLON) {
                getsym();
                test(statBegSys | IDENT | PROCSYM, fsys, 6);
            } else {
                error(5);
            }
        }
        test(statBegSys | IDENT, declBegSys, 7);
    } while (sym & declBegSys);
    
    code[table[initTableIdx].addr].addr = codeAlloIdx;
    table[initTableIdx].addr         = codeAlloIdx;  // start addr of code
    initCodeIdx                      = codeAlloIdx;
    
    gen(Int, 0, dataAlloIdx);
    statement(fsys | SEMICOLON | ENDSYM);
    gen(Opr, 0, 0);  // return
    test(fsys, 0, 8);
    listcode(initCodeIdx);
}