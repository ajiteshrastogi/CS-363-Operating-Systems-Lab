#include <stdio.h>
#include <pthread.h>

// Thread function
void* print_num(void* arg) {
    int num = *(int*)arg;
    printf("Thread received: %d\n", num);
    return NULL;
}

int main() {
    pthread_t t1;
    int value = 42;

    pthread_create(&t1, NULL, print_num, &value);
    pthread_join(t1, NULL);

    return 0;
}
