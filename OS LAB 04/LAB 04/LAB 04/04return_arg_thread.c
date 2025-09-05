#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Thread function to compute square of a number
void* square(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int));  // Allocate memory for result

    *result = num * num;                // Compute square
    pthread_exit(result);              // Return result via pthread_exit
}

int main() {
    pthread_t t1;
    int value = 7;
    int* res = NULL;

    // Create a thread to compute the square
    pthread_create(&t1, NULL, square, &value);

    // Wait for the thread and collect the returned result
    pthread_join(t1, (void**)&res);

    // Print the result
    printf("Square of %d = %d\n", value, *res);

    // Free the dynamically allocated memory
    free(res);

    return 0;
}

