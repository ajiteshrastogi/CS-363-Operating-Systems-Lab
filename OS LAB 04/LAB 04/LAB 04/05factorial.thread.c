#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5  // Number of threads (and factorials to compute)

// Thread function to compute factorial
void* compute_factorial(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int));
    *result = 1;

    for (int i = 1; i <= num; i++) {
        *result *= i;
    }

    pthread_exit(result);  // Return pointer to result
}

int main() {
    pthread_t threads[N];
    int ids[N] = {1, 2, 3, 4, 5};  // Numbers to compute factorial of
    int* results[N];              // To store returned pointers

    // Create threads
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, compute_factorial, &ids[i]);
    }

    // Wait for threads and collect results
    for (int i = 0; i < N; i++) {
        void* res;
        pthread_join(threads[i], &res);
        results[i] = (int*)res;

        printf("Factorial of %d = %d\n", ids[i], *results[i]);

        free(results[i]);  // Free dynamically allocated memory
    }

    return 0;
}
