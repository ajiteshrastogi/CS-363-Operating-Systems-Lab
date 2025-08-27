#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close write end
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            perror("read failed");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0'; // Null-terminate
        printf("Child received message: %s\n", buffer);
        close(pipefd[0]);
    } else {
        // Parent process
        close(pipefd[0]); // Close read end
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("write failed");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]); // Close write end after writing
        wait(NULL);
    }

    return 0;
}
