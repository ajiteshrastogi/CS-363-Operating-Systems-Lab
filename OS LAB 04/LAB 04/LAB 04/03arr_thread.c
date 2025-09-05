#include <stdio.h>
#include <pthread.h>

#define N 5  // Number of threads

void* print_index(void* arg) {
    int index = *(int*)arg;
    printf("Thread %d is running\n", index);
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, print_index, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
