#include "redirect.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "error_handler.h"

// 3 scenarios: space redirect space
// character redirect space
// space redirect character
// character.

// assuming there is only 1 redirect.
// wht happens if I make it null? and decrease argc. ez pz.



bool handle_redirection(int *argc, char **argv, FILE **out) {
    *out = NULL;
    int redirect_count = 0;
    char *redirect_index = NULL;
    size_t string_index = 0;
    size_t arg_index = 0;
    for (size_t i = 0; argv[i] != NULL; i++) {
        char *str = argv[i];
        char *redirect_tmp = NULL;
        while ((redirect_tmp = strchr(str, '>'))) {
            redirect_index = redirect_tmp;
            redirect_count++;
            str = redirect_index + 1;
            string_index = redirect_index - argv[i];
            arg_index = i;
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

    if (redirect_index == argv[0]) {
        print_error();
        // fprintf(stderr, "wish: redirect error, no command found\n");
        return false;
    }

    char *file_index = redirect_index + 1;
    if (*file_index == '\0') {
        file_index = argv[arg_index+1];
        *argc = *argc - 1;
    }
    // find_next;

    if (file_index == NULL) {
        print_error();
        // fprintf(stderr, "wish: too many arguments for redirect\n");
        return false;
    }
    if (string_index == 0) {
        *argc = *argc - 1;
    }
    argv[*argc] = NULL;
    *redirect_index = '\0';
    *out = fopen(file_index, "w");
    if (*out == NULL) {
        fprintf(stderr, "wish: redirect file error %s\n", strerror(errno));
        return false;
    }
    return true;
}
