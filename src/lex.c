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
				sym = -i - 1;
				return;
			}
		}
		sym = SYM_ID;
	} else if (isdigit(ch)) {
		num = 0;
		while (isdigit(ch)) {
			num = num * 10 + ch - '0';
			getch();
		}
	} else if (ch == '=') {

	} else if (ch == ':') {

	} else if (ch == '+') {
		
	} else if (ch == '-') {
		
	} else if (ch == '*') {
		
	} else if (ch == '/') {
		
	} else if (ch == ';') {

	}
}