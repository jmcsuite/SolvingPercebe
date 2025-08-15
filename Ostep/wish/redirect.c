#include "redirect.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "error_handler.h"

bool handle_redirection(int *argc, char **argv, FILE **out) {
    *out = NULL;
    int redirect_count = 0;
    size_t redirect_index = 0;
    for (size_t i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], ">") == 0) {
            redirect_count++;
            redirect_index = i;
        }
    }
    if (redirect_count == 0) {
        return true;
    }
    if (redirect_count > 1) {
        print_error();
        // fprintf(stderr, "wish: redirect command found more than once\n");
        return false;
    }
    if (redirect_index == 0) {
        print_error();
        // fprintf(stderr, "wish: redirect error, no command found\n");
        return false;
    }
    if (redirect_index + 2 != *argc) {
        print_error();
        // fprintf(stderr, "wish: too many arguments for redirect\n");
        return false;
    }
    argv[redirect_index] = NULL;
    *argc = *argc - 2;
    *out = fopen(argv[redirect_index+1], "w");
    if (*out == NULL) {
        fprintf(stderr, "wish: redirect file error %s\n", strerror(errno));
        return false;
    }
    return true;
}
