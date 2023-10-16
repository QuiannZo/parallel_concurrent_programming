#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define MAX_QUEUE_SIZE 10 // Adjust the size according to your needs

void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

bool is_empty(Queue* q) {
    return q->front == q->rear;
}

bool is_full(Queue* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(Queue* q, char* item) {
    pthread_mutex_lock(&q->mutex);
    while (is_full(q)) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

char* dequeue(Queue* q) {
    char* item;
    pthread_mutex_lock(&q->mutex);
    while (is_empty(q)) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    item = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    return item;
}
