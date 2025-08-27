#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: execute "ls -l" using execvp
        char *args[] = {"ls", "-l", NULL};
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE); // Terminate child on exec failure
        }
    } else {
        // Parent process: wait for child to finish
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child ended abnormally.\n");
        }
    }
    return 0;
}
