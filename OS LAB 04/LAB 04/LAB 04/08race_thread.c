#include <stdio.h>
#include <pthread.h>
#include <sched.h>

volatile int counter = 0;

void* inc(void* arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        counter++;
        if ((i & 1023) == 0) {
            sched_yield();
        }
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, inc, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter = %d (expected %d)\n", counter, 2000000);
    return 0;
}
