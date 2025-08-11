#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void reverse(FILE *in, FILE *out) {
    char **save = NULL;
    size_t sz = 1;
    size_t i = 0;
    save = malloc(sz * sizeof(char *));
    for (size_t j = 0; j < sz; ++j) save[j] = NULL;

    size_t n = 0;
    while (getline(&save[i++], &n, in) != -1) {
        if (i == sz) {
            sz = sz * 2;
            save = realloc(save, sz * sizeof(char *));
            if (save == NULL) {
                fprintf(stderr, "malloc failed\n");
            }
            for (size_t j = i; j < sz; j++) save[i] = NULL;
        }
    }

    for (int j = i-1; j >= 0; --j) {
        fprintf(out, "%s", save[j]);
    }
    for (size_t j = 0; j < sz; ++j) {
        free(save[j]);
    }
        
    
    if (errno != 0) {
        fprintf(stderr, "error: %s", strerror(errno));
        exit(1);
    }
}

FILE *handle_file(char *a, const char *mode) {
    FILE *f = fopen(a, mode);
    if (f == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", a);
        exit(1);
    }
    return f;
}
void input_output(char *a, char *b) {
    if (strcmp(a,b) == 0) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }
    
    FILE *f = handle_file(a, "r");
    FILE *g = handle_file(b, "w");
    struct stat b1;
    struct stat b2;

    int status = fstat(fileno(f), &b1);
    if (status != 0) {
        fprintf(stderr, "reverse: stat failed %s", strerror(errno));
        exit(1);
    }
    status = fstat(fileno(g), &b2);
    if (status != 0) {
        fprintf(stderr, "reverse: stat failed %s", strerror(errno));
        exit(1);
    }
    if ((b1.st_dev == b2.st_dev) && (b1.st_ino == b2.st_ino)) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }
    reverse(f,g);
}

void input(char *a) {
    FILE *f = handle_file(a, "r");
    reverse(f, stdout);
}

void no_input() {
    reverse(stdin, stdout);
}

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    if (argc == 3) {
        input_output(argv[1], argv[2]);
        exit(0);
    }
    if (argc == 2) {
        input(argv[1]);
        exit(0);
    }
    if (argc == 1) {
        no_input();
        exit(0);
    }
}
