#include "plzero.h"
#include "interpreter.h"

#include <stdio.h>

int downBase(int base, int lev) {
    int newBase;

    newBase = base;
    while (lev > 0) {  // find base lev levels down
        newBase = stk[newBase];
        --lev;
    }
    return newBase;
}

void interpret() {
    int prog, base, top;      // program-, base-, topstack-registers
    instruction ins;          // instruction register
    
    top = 0;
    base = 1;
    prog = 0;
    stk[1] = 0;
    stk[2] = 0;
    stk[3] = 0;
    
    printf("start PL/0\n");
    do {
        ins = code[prog];
        prog += 1;
        switch (ins.func) {
            case Lit:
                top += 1;
                stk[top] = ins.addr;
                break;
            case Opr:
                switch (ins.addr) {  // operator
                    case 0:       // return
                        top = base - 1;
                        prog = stk[top + 3];
                        base = stk[top + 2];
                        break;
                    case 1:
                        stk[top] = -stk[top];
                        break;
                    case 2:
                        top -= 1;
                        stk[top] += stk[top + 1];
                        break;
                    case 3:
                        top -= 1;
                        stk[top] -= stk[top + 1];
                        break;
                    case 4:
                        top -= 1;
                        stk[top] *= stk[top + 1];
                        break;
                    case 5:
                        top -= 1;
                        stk[top] /= stk[top + 1];
                        break;
                    case 6:
                        stk[top] %= 2;
                        break;
                    case 8:
                        top -= 1;
                        stk[top] = (stk[top] == stk[top + 1]);
                        break;
                    case 9:
                        top -= 1;
                        stk[top] = (stk[top] != stk[top + 1]);
                        break;
                    case 10:
                        top -= 1;
                        stk[top] = (stk[top] < stk[top + 1]);
                        break;
                    case 11:
                        top -= 1;
                        stk[top] = (stk[top] >= stk[top + 1]);
                        break;
                    case 12:
                        top -= 1;
                        stk[top] = (stk[top] > stk[top + 1]);
                        break;
                    case 13:
                        top -= 1;
                        stk[top] = (stk[top] <= stk[top + 1]);
                }
                break;
            case Lod:
                top += 1;
                stk[top] = stk[downBase(base, ins.lev) + ins.addr];
                break;
            case Sto:
                stk[downBase(base, ins.lev) + ins.addr] = stk[top];
                printf("%10d\n", stk[top]);
                top -= 1;
                break;
            case Cal:  // generate new block mark
                stk[top + 1] = downBase(base, ins.lev);
                stk[top + 2] = base;
                stk[top + 3] = prog;
                base = top + 1;
                prog = ins.addr;
                break;
            case Int:
                top += ins.addr;
                break;
            case Jmp:
                prog = ins.addr;
                break;
            case Jpc:
                if (stk[top] == 0) {
                    prog = ins.addr;
                }
                --top;
        }
    } while (prog);
    printf("end PL/0\n");
}