#include <stdio.h>
#include <stdlib.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void checkFile(char* file, int limit) {
    int nlines = 1;
    int x = 0;
    int out = 0;
    int prec = -1;
    FILE* f = fopen(file, "r");
    if (!f) {
        fprintf(stderr, "%sError%s : file not found\n", RED, RESET);
        exit(1);
    }
    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n') {
            nlines++;
            x = 0;
        } else {
            x++;
            if (x > limit) {
                if (nlines != prec) {
                    prec = nlines;
                    out++;
                    
                    fprintf(stderr, "Line %s%d%s is too long\n", CYAN, nlines, RESET);
                }
            }
        }
        c = fgetc(f);
    }
    if (out) {
        printf("\n");
        if (out == 1) {
            printf("%s%d%s line out of %s%d%s is too long\n", CYAN, out, RESET, GREEN, nlines, RESET);
        } else {
            printf("%s%d%s lines out of %s%d%s are too long\n", CYAN, out, RESET, GREEN, nlines, RESET);
        }
    } else {
        printf("%s%d%s line out of %s%d%s is too long\n", CYAN, out, RESET, GREEN, nlines, RESET);
    }

}

int main(int argc, char *argv[]) {
    checkFile(argv[1], atoi(argv[2]));
}