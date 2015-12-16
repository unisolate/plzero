#ifndef _INTERPRETER_
#define _INTERPRETER_

#define STK_SIZE 50000  // size of stack

extern char *resWord[RES_NUM];

int stk[STK_SIZE];      // datastore

int downBase(int base, int lev);
void interpret();

#endif