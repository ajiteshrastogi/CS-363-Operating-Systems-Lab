#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void* worker(void* arg) {
    int id = *(int*)arg;

    sem_wait(&sem);
    printf("Thread %d entered\n", id);
    sleep(1);
    printf("Thread %d leaving\n", id);
    sem_post(&sem);

    return NULL;
}

int main() {
    pthread_t t[5];
    int ids[5];

    sem_init(&sem, 0, 2);  // Initialize semaphore with value 2 (max 2 threads at a time)

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&sem);
    return 0;
}
