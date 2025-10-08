#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define ITEMS_TO_PRODUCE 5

int buffer[SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void *producer(void *arg) {
    int item, id = *((int *)arg);

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Producer %d produced %d at position %d\n", id, item, in);
        in = (in + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }

    printf("Producer %d finished producing.\n", id);
    return NULL;
}

void *consumer(void *arg) {
    int item, id = *((int *)arg);

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumer %d consumed %d from position %d\n", id, item, out);
        out = (out + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }

    printf("Consumer %d finished consuming.\n", id);
    return NULL;
}

int main() {
    pthread_t ptid[2], ctid[2];
    int pid[2] = {1, 2}, cid[2] = {1, 2};

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 2; i++)
        pthread_create(&ptid[i], NULL, producer, &pid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&ctid[i], NULL, consumer, &cid[i]);

    for (int i = 0; i < 2; i++)
        pthread_join(ptid[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(ctid[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("All producers and consumers have finished. Program exiting.\n");
    return 0;
}

