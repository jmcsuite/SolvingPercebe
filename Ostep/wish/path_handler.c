#include "path_handler.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *init_path[] = {
    "/usr/bin/"
};

char **PATHS = init_path;

void handle_path(int argc, char **argv) {
    if (PATHS != init_path) {
        for (size_t i = 0; PATHS[i] != NULL; i++) {
            free(PATHS[i]);
        }
        free(PATHS);
    }
    PATHS = NULL;

    PATHS = malloc(argc * sizeof(const char*));
    if (PATHS == NULL) {
        fprintf(stderr, "wish: malloc failed %s", strerror(errno));
        exit(1);
    }
    for (int i = 0; i < argc; i++) PATHS[i] = NULL;
    for (int i = 0; i < argc-1; i++) {
        size_t sz = strlen(argv[i+1]) + 1;
        PATHS[i] = malloc(sz * sizeof(char));
        strcpy(PATHS[i], argv[i+1]);
    }
}
