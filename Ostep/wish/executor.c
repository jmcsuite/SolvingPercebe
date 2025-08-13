#include "executor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "directory.h"

const char* _PATH_ = "/usr/bin/";

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

// TODO(different tests) : one for different commands, other for different parsing.
bool verify_cmd(const char *path) {
    if (access(path, X_OK) == -1) {
        return false;
    }
    return true;
}

void run_command(char **argv) {
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "wish: fork failed %s\n", strerror(errno));
        exit(1);
    }
    // child process.
    if (pid == 0) {
        execv(argv[0], argv);
        fprintf(stderr, "wish: execv error %s\n", strerror(errno));
        exit(-1);
    }
    if (wait(NULL) == -1) {
        fprintf(stderr, "wish: wait failed %s\n", strerror(errno));
        exit(1);
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
        // handle_path();
        return true;
    }
    return false;
}

// void run_cmd(int argc, char *full_path, char **argv);

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

    // handle non-custom cmd.
    // mallocs full_path.
    char *full_path = get_cmd(_PATH_, argv[0]);
    if (!verify_cmd(full_path)) {
        fprintf(stderr, "wish: can't run command, error=%s\n", strerror(errno));
        free(full_path);
        exit(1);
    }

    argv[0] = full_path;
    run_command(argv);
    free(full_path);
}
