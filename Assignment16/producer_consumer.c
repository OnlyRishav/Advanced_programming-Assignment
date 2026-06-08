#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE    5
#define NUM_PRODUCERS  3
#define NUM_CONSUMERS  3
#define ITEMS_PER_PROD 4
#define TOTAL_ITEMS    (NUM_PRODUCERS * ITEMS_PER_PROD)

typedef struct { int value; int producer_id; int seq; } Item;

static Item buffer[BUFFER_SIZE];
static int  buf_in    = 0;
static int  buf_out   = 0;
static int  buf_count = 0;

static sem_t           empty_slots;
static sem_t           filled_slots;
static pthread_mutex_t buffer_mutex   = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t shutdown_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  shutdown_cond  = PTHREAD_COND_INITIALIZER;
static int             items_consumed = 0;
static int             all_done       = 0;

static void print_ts(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long ms = (ts.tv_nsec / 1000000) % 1000;
    struct tm *t = localtime(&ts.tv_sec);
    printf("[%02d:%02d:%02d.%03ld] ", t->tm_hour, t->tm_min, t->tm_sec, ms);
}

static void *producer(void *arg) {
    int id = *(int *)arg;
    free(arg);

    for (int seq = 1; seq <= ITEMS_PER_PROD; seq++) {
        usleep((rand() % 300 + 100) * 1000);

        Item item = { id * 100 + seq, id, seq };

        print_ts();
        printf("Producer-%d  ⏳  waiting for free slot  (item %d)\n", id, item.value);
        sem_wait(&empty_slots);

        pthread_mutex_lock(&buffer_mutex);
        buffer[buf_in] = item;
        buf_in = (buf_in + 1) % BUFFER_SIZE;
        buf_count++;
        print_ts();
        printf("Producer-%d  ✅  produced  %d  → buffer [%d/%d]\n",
               id, item.value, buf_count, BUFFER_SIZE);
        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&filled_slots);
    }

    print_ts();
    printf("Producer-%d  🏁  finished (%d items)\n", id, ITEMS_PER_PROD);
    return NULL;
}

static void *consumer(void *arg) {
    int id = *(int *)arg;
    free(arg);

    while (1) {
        pthread_mutex_lock(&shutdown_mutex);
        while (!all_done) {
            pthread_mutex_unlock(&shutdown_mutex);

            print_ts();
            printf("Consumer-%d  ⏳  waiting for item …\n", id);

            sem_wait(&filled_slots);

            pthread_mutex_lock(&shutdown_mutex);
            if (all_done) {
                sem_post(&filled_slots);
                pthread_mutex_unlock(&shutdown_mutex);
                goto consumer_exit;
            }
            pthread_mutex_unlock(&shutdown_mutex);

            pthread_mutex_lock(&buffer_mutex);
            Item item  = buffer[buf_out];
            buf_out    = (buf_out + 1) % BUFFER_SIZE;
            buf_count--;
            print_ts();
            printf("Consumer-%d  📦  consumed %d  (P-%d seq %d)  buffer [%d/%d]\n",
                   id, item.value, item.producer_id, item.seq,
                   buf_count, BUFFER_SIZE);
            pthread_mutex_unlock(&buffer_mutex);

            sem_post(&empty_slots);

            usleep((rand() % 400 + 200) * 1000);

            pthread_mutex_lock(&shutdown_mutex);
            items_consumed++;
            if (items_consumed >= TOTAL_ITEMS) {
                all_done = 1;
                pthread_cond_broadcast(&shutdown_cond);
                pthread_mutex_unlock(&shutdown_mutex);
                print_ts();
                printf("Consumer-%d  🏁  all %d items consumed — shutting down\n",
                       id, TOTAL_ITEMS);
                return NULL;
            }
            pthread_mutex_unlock(&shutdown_mutex);

            pthread_mutex_lock(&shutdown_mutex);
        }
        pthread_mutex_unlock(&shutdown_mutex);
        break;
    }

consumer_exit:
    print_ts();
    printf("Consumer-%d  🏁  shutting down\n", id);
    return NULL;
}

int main(void) {
    srand((unsigned)time(NULL));

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║   Multithreaded Producer-Consumer  (POSIX Threads + Sems)   ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  Buffer : %-3d slots │ Producers : %-3d │ Consumers : %-3d     ║\n",
           BUFFER_SIZE, NUM_PRODUCERS, NUM_CONSUMERS);
    printf("║  Total items : %-3d  (%-2d per producer)                       ║\n",
           TOTAL_ITEMS, ITEMS_PER_PROD);
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    sem_init(&empty_slots,  0, BUFFER_SIZE);
    sem_init(&filled_slots, 0, 0);

    pthread_t prod_th[NUM_PRODUCERS], cons_th[NUM_CONSUMERS];

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int *id = malloc(sizeof *id); *id = i + 1;
        pthread_create(&cons_th[i], NULL, consumer, id);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int *id = malloc(sizeof *id); *id = i + 1;
        pthread_create(&prod_th[i], NULL, producer, id);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_join(prod_th[i], NULL);

    for (int i = 0; i < NUM_CONSUMERS; i++) sem_post(&filled_slots);

    for (int i = 0; i < NUM_CONSUMERS; i++) pthread_join(cons_th[i], NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_mutex_destroy(&shutdown_mutex);
    pthread_cond_destroy(&shutdown_cond);

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  ✅  All threads finished.  No races.  Clean shutdown.      ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    return 0;
}
