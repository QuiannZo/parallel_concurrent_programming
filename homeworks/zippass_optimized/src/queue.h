#include <pthread.h>
#include <semaphore.h>

#define QUEUE_SIZE 100

typedef struct {
    char* items[QUEUE_SIZE];
    int front, rear;
    sem_t empty, full, mutex;
} Queue;

void initialize_queue(Queue* q);

void enqueue(Queue* q, char* item);

char* dequeue(Queue* q);

bool is_queue_empty(Queue* q);