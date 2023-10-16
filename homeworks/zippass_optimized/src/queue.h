#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Given by ChatGPT. I must declare a constant here.
#define MAX_QUEUE_SIZE 10 // Adjust the size according to your needs

typedef struct {
    char* items[MAX_QUEUE_SIZE];
    int front, rear;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty, not_full;
} Queue;

void init_queue(Queue* q);

bool is_empty(Queue* q);

bool is_full(Queue* q);

void enqueue(Queue* q, char* item);

char* dequeue(Queue* q);