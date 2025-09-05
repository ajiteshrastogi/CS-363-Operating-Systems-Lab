// Assignment 
// Create a program that reads N, swaps N threads prints its index exactly once the main thread must call pthread_join on all thread and only then print 'Done'.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_index(void* arg) {
    int index = *(int*)arg;
    printf("Thread %d\n", index);
    return NULL;
}

int main() {
    int N;
    printf("Enter number of threads: ");
    scanf("%d", &N);

    pthread_t* threads = malloc(N * sizeof(pthread_t));
    int* ids = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, print_index, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Done\n");

    free(threads);
    free(ids);
    return 0;
}
