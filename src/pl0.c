#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char *src_name = NULL;
    char *bin_name = NULL;
    int c;

    opterr = 0;
    while ((c = getopt(argc, argv, "o:")) != -1) {
        switch (c) {
            case 'o':
                bin_name = optarg;
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
        fprintf(stderr, "Error: No input file specified.\n");
        return 1;
    }
    if (argc - optind > 1) {
        fprintf(stderr, "Error: Too many arguments.\n");
        return 1;
    }

    src_name = argv[optind];
    if (bin_name == NULL) {
        bin_name = src_name;
    }

    init();

    return 0;
}