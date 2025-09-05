#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

// Thread function
void* check_even_odd(void* arg) {
    int id = *(int*)arg;

    if (id % 2 == 0) {
        printf("ID %d is even\n", id);
    } else {
        printf("ID %d is odd\n", id);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, check_even_odd, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
