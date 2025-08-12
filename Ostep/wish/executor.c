#include "executor.h"

#include <stdio.h>

void verify_path();

void execute(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        printf("jmarquina: %s", argv[i]);
        // 1) verificar path;
        // TODO(hay que usar, execv, osea hay que hacer la busqueda del path manualmente);
        // TODO(mover el path define aqui), 
        // TODO(access("/bin/ls", X_OK))
    }
}
