#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex, mutex;
int read_count = 0, shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 2; i++) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("Reader %d reads shared_data = %d (active readers = %d)\n", id, shared_data, read_count);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) sem_post(&rw_mutex);
        sem_post(&mutex);
        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 2; i++) {
        sem_wait(&rw_mutex);
        shared_data += 10;
        printf("Writer %d updates shared_data = %d\n", id, shared_data);
        sleep(1);
        sem_post(&rw_mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r[2], w[2];
    int id[2] = {1, 2};
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 2; i++) {
        pthread_create(&r[i], NULL, reader, &id[i]);
        pthread_create(&w[i], NULL, writer, &id[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}