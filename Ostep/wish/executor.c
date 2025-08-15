#include "executor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "directory.h"
#include "path_handler.h"
#include "redirect.h"
#include "error_handler.h"

int running_subprocess = 0;

char *get_cmd(const char *path, const char *name) {
    size_t full_size = strlen(path) + strlen(name) + 1;
    char *cmd = malloc(full_size * sizeof(char));
    if (cmd == NULL) {
        fprintf(stderr, "wish: malloc failed\n");
        exit(1);
    }
    for (size_t i = 0; i < full_size; i++){
        cmd[i] = '\0';
    }
    cmd = strcat(cmd, path);
    cmd = strcat(cmd, name);
    return cmd;
}

bool verify_cmd(const char *path) {
    if (access(path, X_OK) == -1) {
        return false;
    }
    return true;
}

void run_command(char **argv, FILE* out) {
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "wish: fork failed %s\n", strerror(errno));
        exit(1);
    }
    // child process.
    if (pid == 0) {
        if (out != NULL) {
            if (dup2(fileno(out), fileno(stdout)) == -1) {
                fprintf(stderr, "wish: dup2 error%s\n", strerror(errno));
                exit(-1);
            }
            if (dup2(fileno(out), fileno(stderr)) == -1) {
                fprintf(stderr, "wish: dup2 error%s\n", strerror(errno));
                exit(-1);
            }
            fclose(out);
        }
        execv(argv[0], argv);
        fprintf(stderr, "wish: execv error %s\n", strerror(errno));
        exit(-1);
    }
    running_subprocess += 1;
}

void wait_all() {
    while (running_subprocess > 0) {
        if (wait(NULL) == -1) {
            fprintf(stderr, "wish: wait failed %s\n", strerror(errno));
            exit(1);
        }
        running_subprocess -= 1;
    }
}

bool handle_wish_cmd(int argc, char **argv) {
    if (strcmp("cd", argv[0]) == 0) {
        handle_cd(argc, argv);
        return true;
    }
    if (strcmp("exit", argv[0]) == 0) {
        handle_exit(argc, argv);
        return true;
    }
    if (strcmp("path", argv[0]) == 0) {
        handle_path(argc, argv);
        return true;
    }
    return false;
}

char *get_full_path(int argc, char **argv) {
    char *full_path = NULL;
    for (size_t i = 0; PATHS[i] != NULL; i++) {
        full_path = get_cmd(PATHS[i], argv[0]);
        if (verify_cmd(full_path)) break;
        free(full_path);
        full_path = NULL;
    }
    return full_path;
}


// Don't modify the strings pointed by argv!.
// It is safe to change which strings argv points, but not the underlying
// strings.
// Argv last arguments points to NULL;
void execute(int argc, char **argv) {
    if (argv[argc] != NULL) {
        fprintf(stderr,
                "wish: array of arguments needs to be nullptr terminated\n");
        exit(1);
    }
    if (handle_wish_cmd(argc, argv)) return;


    FILE *out = NULL;
    if (!handle_redirection(&argc, argv, &out)) {
        return;
    }
    char* full_path = get_full_path(argc, argv);
    if (full_path == NULL) {
        print_error();
        return;
    }

    argv[0] = full_path;
    run_command(argv, out);
    free(full_path);
}
