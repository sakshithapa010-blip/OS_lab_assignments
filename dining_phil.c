#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t chopstick[N], room;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id, right = (id + 1) % N;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    sem_wait(&room);
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&chopstick[right]);
    sem_post(&chopstick[left]);
    sem_post(&room);

    printf("Philosopher %d finished eating\n", id);
    return NULL;
}

int main() {
    pthread_t p[N];
    int ids[N];
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        sem_init(&chopstick[i], 0, 1);
    }
    for (int i = 0; i < N; i++) pthread_create(&p[i], NULL, philosopher, &ids[i]);
    for (int i = 0; i < N; i++) pthread_join(p[i], NULL);
    for (int i = 0; i < N; i++) sem_destroy(&chopstick[i]);
    sem_destroy(&room);
    return 0;
}