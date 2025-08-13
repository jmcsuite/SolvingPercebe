#include "executor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// void run_cmd(int argc, char *full_path, char **argv);

// Don't modify the strings pointed by argv!.
// It is safe to change which strings argv points, but not the underlying
// strings.
// Argv last arguments points to NULL;
void execute(int argc, char **argv) {
    char *full_path = get_cmd(_PATH_, argv[0]);
    if (!verify_cmd(full_path)) {
        fprintf(stderr, "wish: can't run command, error=%s\n", strerror(errno));
        exit(1);
        // free(full_path);
    }
    // printf("jmarquina: found command"); NOW EXECUTE COMMAND
}
