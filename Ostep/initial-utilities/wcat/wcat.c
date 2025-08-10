#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wcat(char *file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        // TODO : (jmarquina) - log error to stderr in prod.
        fprintf(stdout, "wcat: cannot open file\n");
        exit(1);
    }
    const size_t size = 5000;
    char buffer[size];

    while (fgets(buffer, size, f)) {
        printf("%s", buffer);
    }

    int status = fclose(f);
    if (status != 0) {
        fprintf(stderr, "wcat: error closing file %s", strerror(errno));
    }
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        wcat(argv[i]);
    }
    exit(0);
}
