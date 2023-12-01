#include <pthread.h>
#include <semaphore.h>

#define QUEUE_SIZE 100

/**
 * @struct Queue.
 * @brief thread-safe queue with semaphores.
 */
typedef struct {
    char* items[QUEUE_SIZE];
    int front, rear;
    sem_t empty, full, mutex;
} Queue;

/**
 * @brief Initializes the queue.
 * @param q A pointer to the Queue struct to be initialized.
 */
void initialize_queue(Queue* q);

/**
 * @brief Enqueues an item into the queue.
 * @param q A pointer to the Queue struct.
 * @param item The item to enqueue.
 */
void enqueue(Queue* q, char* item);

/**
 * @brief Dequeues an item from the queue.
 * @param q A pointer to the Queue struct.
 * @return The item dequeued from the queue.
 */
char* dequeue(Queue* q);

/**
 * @brief Checks if the queue is empty.
 * @param q A pointer to the Queue struct.
 * @return 'true' if the queue is empty, else 'false'.
 */
bool is_queue_empty(Queue* q);