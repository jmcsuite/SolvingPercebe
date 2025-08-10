// redirect.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **argv1;
char **argv2;
int argc1;
int argc2;


int size_malloc(char *arg) {
    return strlen(arg) + 1; // Adding NULL Character padding;
}

void copy(char *argv[], char ***dest, int pos, int count) {
    (*dest) = (char **)malloc((count+1) * sizeof(char *));
    (*dest)[count] = NULL;
    for (int i=0; i<count; i++) {
        (*dest)[i] = (char *)malloc(size_malloc(argv[pos + i]) * sizeof(char));
        strcpy((*dest)[i], argv[pos + i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: redirect cmd1 args*** \\| cmd2 args***\n");
        return 0;
    }
    int sep = -1;
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            sep = i;
            break;
        }
    }
    if (sep == -1) {
        printf("Missing \\|\n");
        printf("Usage: redirect cmd1 args*** \\| cmd2 args***\n");
        return 0;
    }

    argc1 = sep-1;
    argc2 = argc - sep - 1;
    copy(argv, &argv1, 1, argc1);
    copy(argv, &argv2, sep+1, argc2);
   
   int pipefd[2];
   if (pipe(pipefd) == -1) {
       printf("ERROR pipe");
       return 0;
   }

   int pid = fork();
   if (pid < 0) {
      printf("Error child1\n");
      return 0;
   } 
   else if (pid == 0) {
       // CHILD;
       close(pipefd[0]); // close read end;
       close(STDOUT_FILENO);
       dup(pipefd[1]);
       close(pipefd[1]);
       execvp(argv1[0], argv1);
       printf("Exec call failed\n");
   }

   int pid2 = fork();
   if (pid2 < 0) {
       printf("Error child1\n");
       return 0;
   }
   else if (pid2 == 0) {
       // CHILD;
       close(pipefd[1]); // close write end.
       close(STDIN_FILENO);
       dup(pipefd[0]); // duplicate read end;
       close(pipefd[0]);
       execvp(argv2[0], argv2);
       printf("Exec call failed\n");
   }
   close(pipefd[0]);
   close(pipefd[1]);
   wait(NULL);
   wait(NULL);
   //wait(NULL);
}
