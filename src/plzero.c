#include "plzero.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

char *resWord[RES_NUM] = {
    "begin",
    "call",
    "const",
    "do",
    "end",
    "if",
    "odd",
    "procedure",
    "then",
    "var",
    "while"
};

int wordSym[256] = {
    BEGINSYM,
    CALLSYM,
    CONSTSYM,
    DOSYM,
    ENDSYM,
    IFSYM,
    ODDSYM,
    PROCSYM,
    THENSYM,
    VARSYM,
    WHILESYM
};

void error(int n) {
    int i;

    printf(" ****");
    for (i = 1; i <= charCnt - 1; i++) {
        printf(" ");
    }
    printf("^%2d\n", n);
    err++;
}

void init() {
    for (int i = 11; i < 256; i++) {
        wordSym[i] = NUL;
    }
    wordSym['+'] = PLUS;
    wordSym['-'] = MINUS;
    wordSym['*'] = TIMES;
    wordSym['/'] = SLASH;
    wordSym['('] = LPAREN;
    wordSym[')'] = RPAREN;
    wordSym['='] = EQL;
    wordSym[','] = COMMA;
    wordSym['.'] = PERIOD;
    wordSym[';'] = SEMICOLON;

    strcpy(mnemonic[Lit], "Lit");
    strcpy(mnemonic[Opr], "Opr");
    strcpy(mnemonic[Lod], "Lod");
    strcpy(mnemonic[Sto], "Sto");
    strcpy(mnemonic[Cal], "Cal");
    strcpy(mnemonic[Int], "int");
    strcpy(mnemonic[Jmp], "Jmp");
    strcpy(mnemonic[Jpc], "Jpc");

    declBegSys = CONSTSYM | VARSYM  | PROCSYM;
    statBegSys = BEGINSYM | CALLSYM | IFSYM  | WHILESYM;
    facBegSys  = IDENT    | NUMBER  | LPAREN;
    
    err         = 0;
    charCnt     = 0;
    codeAlloIdx = 0;
    lineLen     = 0;
    ch          = ' ';
}

int main(int argc, char *argv[]) {
    char *srcName = NULL;
    char *binName = NULL;
    int opt;

    opterr = 0;
    while ((opt = getopt(argc, argv, "o:")) != -1) {
        switch (opt) {
            case 'o':
                binName = optarg;
                break;
            case '?':
                if (optopt == 'o') {
                    fprintf(stderr, 
                        "Error: Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, 
                        "Error: Unknown option `-%c'.\n", optopt);
                } else {
                    fprintf(stderr, 
                        "Error: Unknown option character `\\x%x'.\n", optopt);
                }
                return 1;
            default:
                abort();
        }
    }

    if (argc - optind == 0) {
        fprintf(stderr, "error: no input file specified\n");
        return 1;
    }
    if (argc - optind > 1) {
        fprintf(stderr, "error: too many arguments\n");
        return 1;
    }

    srcName = argv[optind];
    if (binName == NULL) {
        binName = srcName;
    }
    
    if ((srcFile = fopen(srcName, "r")) == NULL) {
        printf("File %s can't be opened.\n", srcName);
        exit(1);
    }

    init();
    getsym();
    
    lev      = 0;
    tableIdx = 0;
    
    block(declBegSys | statBegSys | PERIOD);
    
    if (sym != PERIOD) {
        error(9);
    }
    
    if (err == 0) {
        interpret();
    } else {
        printf("errors in PL/0 program\n");
    }
    
    fclose(srcFile);
    return 0;
}