#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READS 3   // Number of read operations per reader
#define NUM_WRITES 3  // Number of write operations per writer

sem_t x, wrt;
int readcount = 0;  // Number of readers currently reading

// Reader thread function
void *reader(void *arg) {
    int id = *((int *)arg);

    for (int i = 0; i < NUM_READS; i++) {
        sem_wait(&x);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);  // First reader locks writer
        sem_post(&x);

        printf("Reader %d is reading the shared database...\n", id);
        sleep(1);

        sem_wait(&x);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);  // Last reader unlocks writer
        sem_post(&x);

        printf("Reader %d has finished reading.\n", id);
        sleep(1);
    }

    printf("Reader %d is done.\n", id);
    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int id = *((int *)arg);

    for (int i = 0; i < NUM_WRITES; i++) {
        printf("Writer %d is waiting to write to the database...\n", id);
        sem_wait(&wrt);

        printf("Writer %d is writing to the shared database...\n", id);
        sleep(2);

        sem_post(&wrt);
        printf("Writer %d has finished writing.\n", id);
        sleep(1);
    }

    printf("Writer %d is done.\n", id);
    return NULL;
}

int main() {
    pthread_t rtid[3], wtid;
    int r[3] = {1, 2, 3};
    int w = 1;

    sem_init(&x, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create 3 reader threads
    for (int i = 0; i < 3; i++)
        pthread_create(&rtid[i], NULL, reader, &r[i]);

    // Create 1 writer thread
    pthread_create(&wtid, NULL, writer, &w);

    // Wait for all readers to finish
    for (int i = 0; i < 3; i++)
        pthread_join(rtid[i], NULL);

    // Wait for writer to finish
    pthread_join(wtid, NULL);

    printf("All readers and the writer have finished. Program exiting.\n");
    return 0;
}

