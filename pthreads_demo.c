#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* worker(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d executing (TID = %lu)\n", id, (unsigned long)pthread_self());
    int *res = malloc(sizeof(int));
    *res = id * 10;
    pthread_exit(res);
}

int main() {
    pthread_t t[2];
    int ids[2] = {1, 2};
    void *ret;

    for (int i = 0; i < 2; i++) {
        pthread_create(&t[i], NULL, worker, &ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(t[i], &ret);
        printf("Main thread joined Thread %d: returned %d\n", ids[i], *(int*)ret);
        free(ret);
    }
    return 0;
}