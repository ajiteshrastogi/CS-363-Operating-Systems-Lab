#include <stdio.h>
#include <pthread.h>

#define ITERS 1000000

int counter = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* inc(void* arg) {
    int i;
    for (i = 0; i < ITERS; i++) {
        pthread_mutex_lock(&m);
        counter++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, inc, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter = %d (expected %d)\n", counter, 2 * ITERS);

    pthread_mutex_destroy(&m);
    return 0;
}
