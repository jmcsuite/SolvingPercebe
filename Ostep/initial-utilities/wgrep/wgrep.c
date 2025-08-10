#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void match(char *term, FILE *file);
void read_file(char *term, char *file_name);

void read_file(char *term, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
    }
    match(term, file);
    if (fclose(file) != 0) {
        fprintf(stderr, "wgrep: error closing file %s", strerror(errno));
    }
}


void match(char *term, FILE *file) {
    char *line = NULL;
    size_t bytes = 0;
    while (getline(&line, &bytes, file) != -1) {
        if (strstr(line, term) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc == 2) {
        match(argv[1], stdin);
        exit(0);
    }
    for (int i = 2; i < argc; i++) {
        read_file(argv[1], argv[i]);
    }
}
