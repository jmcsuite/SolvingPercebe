// TODO: handle file starts with same characater as first file!!
#include <stdio.h>
#include <stdlib.h>


void write(int n, char c) {
    if (c == EOF) return;
    fwrite(&n, 1, sizeof(int), stdout);
    fwrite(&c, 1, sizeof(char), stdout);
    // printf("n: %d, c: %c", n, c);
}

char c = EOF;
int n = 0;
void process(FILE* file) {
    int buffer_size = 5000;
    char buffer[buffer_size];
    while (fgets(buffer, buffer_size, file) != NULL) {
        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] != c) {
                write(n, c);
                n = 0;
                c = buffer[i];
            }
            ++n;
        }
    }
}

void wzip(char* file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "wzip: can't open file\n");
        exit(1);
    }
    process(f);
    if (fclose(f) != 0) {
        fprintf(stderr, "wzip: can't close file\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i=1; i<argc; i++) {
        wzip(argv[i]);
    }
    write(n,c);
}
