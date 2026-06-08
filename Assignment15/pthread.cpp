#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 4
#define INCREMENTS_PER_THREAD 1000000

long long counter = 0;
pthread_mutex_t lock;

void *increment_without_mutex(void *arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        counter++;
    }

    return NULL;
}

void *increment_with_mutex(void *arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        pthread_mutex_lock(&lock);

        counter++;

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void) {
    pthread_t threads[THREAD_COUNT];

    printf("=== Without Mutex ===\n");

    counter = 0;

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment_without_mutex, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %d\n", THREAD_COUNT * INCREMENTS_PER_THREAD);
    printf("Actual counter value:   %lld\n", counter);

    printf("\n=== With Mutex ===\n");

    counter = 0;
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment_with_mutex, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %d\n", THREAD_COUNT * INCREMENTS_PER_THREAD);
    printf("Actual counter value:   %lld\n", counter);

    pthread_mutex_destroy(&lock);

    return 0;
}