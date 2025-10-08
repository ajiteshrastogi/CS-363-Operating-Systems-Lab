#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5          // Number of philosophers
#define EAT_LIMIT 1  // Number of times each philosopher eats

sem_t chopstick[N];
int eat_count[N] = {0};  // Track how many times each philosopher has eaten

void *philosopher(void *num) {
    int id = *(int *)num;

    while (eat_count[id] < EAT_LIMIT) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        eat_count[id]++;
        printf("Philosopher %d finished eating %d time(s) and put down chopsticks.\n",
               id, eat_count[id]);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
    }

    printf("Philosopher %d is done eating.\n", id);
    return NULL;
}

int main() {
    pthread_t tid[N];
    int philosopher_ids[N];

    // Initialize semaphores (one for each chopstick)
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    // Create threads for each philosopher
    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for all philosophers to finish
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    printf("All philosophers have eaten once. Program exiting.\n");
    return 0;
}

