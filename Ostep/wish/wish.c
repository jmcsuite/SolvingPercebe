#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/bin/ls"

bool batch_mode = false;

void process_line(char *buffer, size_t sz) {
    char *line = NULL;
    while (line = strsep(&buffer, " "), line != NULL) {
        printf("jmarquina: %s\n", line);
    }
    // TODO(notes): // strsep, read the manulal, it overwrites the first char
    // that is a sep character with null, and sets buffer to point to the next 
    // character. Bad stuff happens if null character is the separating character
    // We can add tab to the delimiter list.
    // We can simply skip emtpy strings, (idk how a user would input a 
    // delimiter character (atm).
}

void wish(FILE *f) {
    char *buffer = NULL;
    size_t size = 0;
    while (getline(&buffer, &size, f) != -1) {
        process_line(buffer, size); 
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
