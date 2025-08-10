#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int x, char c) {
    for (int i=0; i<x; i++) printf("%c", c);
}

void process(FILE* file) {
    int x;
    char c;
    while (fread(&x, 1, sizeof(int), file) != 0 && 
            fread(&c, 1, sizeof(char), file) != 0) 
    {
        print(x, c);
    }
}

void wunzip(char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "wunzip: can't open file\n");
        exit(1);
    }
    process(f);
    if (fclose(f) != 0) {
        fprintf(stderr, "wunzip: can't close file. Error: %s", strerror(errno));
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        wunzip(argv[i]);
    }
}
