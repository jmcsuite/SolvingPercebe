// wish.c
// command line shell.
#include "executor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool batch_mode = false;

void process_line(char *buffer, size_t sz) {
    int args_sz = 2;
    char **args = malloc(args_sz * sizeof(char *));
    if (args == NULL) {
        fprintf(stderr, "wish: malloc error %s", strerror(errno));
        exit(1);
    }
    for (size_t i = 0; i < args_sz; i++) args[i] = NULL;
    int argc = 0;

    // Bad stuff happens if null character is the separating character
    // We can add tab to the delimiter list.
    while (args[argc] = strsep(&buffer, " \t\n"), args[argc] != NULL) {
        if (args[argc][0] == '\0') {
            continue;
        }
        argc++;
        if (argc+1 == args_sz) {
            args_sz = args_sz * 2;
            args = realloc(args, args_sz * sizeof(char *));
            if (args == NULL) {
                fprintf(stderr, "wish: realloc error %s", strerror(errno));
                exit(1);
            }
            for (int i = argc; i < args_sz; i++) {
                args[i] = NULL;
            }
        }
    }
    execute(argc, args);
    free(args);

    //TODO(next steps): // let's execute something from PATH using this chars 
    //  First wi would need to check path.
}

void wish(FILE *f) {
    char *buffer = NULL;
    size_t size = 0;
    // TODO : maybe in batch job print a nl?
    if (!batch_mode) {
        printf("wish> ");
    }
    while (getline(&buffer, &size, f) != -1) {
        process_line(buffer, size); 
        if (!batch_mode) {
            printf("wish> ");
        }
    }
    free(buffer);
    exit(0);
}

void handle_file(char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "wish: can't open file");
    }
    wish(f);
    fclose(f);
}

void handle_interactive() {
    wish(stdin);
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, "wish: too many arguments");
        exit(1);
    }
    if (argc == 2) {
        batch_mode = true;
        handle_file(argv[1]);
        exit(0);
    }
    if (argc == 1) {
        batch_mode = false;
        handle_interactive();
        exit(0);
    }
}
