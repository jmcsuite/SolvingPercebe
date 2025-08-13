#include "directory.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handle_cd(int argc, char **argv) {
    if (argc <= 1 || argc > 2) {
        fprintf(stderr, "wish: cd <dir>\n");
        return;
    }
    if(chdir(argv[1]) == -1) {
        fprintf(stderr, "wish: chdir error %s\n", strerror(errno));
    }
}

void handle_exit(int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "wish: exit needs no arguments\n");
        return;
    }
    exit(0);
}
