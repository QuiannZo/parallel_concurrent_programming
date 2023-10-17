#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "queue.h"

void initialize_queue(Queue* q) {
    q->front = q->rear = 0;
    sem_init(&q->empty, 0, QUEUE_SIZE);
    sem_init(&q->full, 0, 0);
    sem_init(&q->mutex, 0, 1);
}

void enqueue(Queue* q, char* item) {
    sem_wait(&q->empty);
    sem_wait(&q->mutex);
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    sem_post(&q->mutex);
    sem_post(&q->full);
}

char* dequeue(Queue* q) {
    char* item;
    sem_wait(&q->full);
    sem_wait(&q->mutex);
    item = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    sem_post(&q->mutex);
    sem_post(&q->empty);
    return item;
}

bool is_queue_empty(Queue* q) {
    return q->front == q->rear;
}