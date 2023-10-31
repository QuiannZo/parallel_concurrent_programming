#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

// thread_shared_data_t
typedef struct shared_data {
    sem_t** can_greet;
    uint64_t thread_count;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
    uint64_t thread_number;  // rank
    shared_data_t* shared_data;
} private_data_t;

/**
 * @brief ...
 */
void* greet(void* data);
int create_threads(shared_data_t* shared_data);

int main(int argc, char* argv[]) {
    int error = EXIT_SUCCESS;
    // create thread_count as the result of converting argv[1] to an integer
    // thread_count := integer(argv[1])
    uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
        if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
        } else {
            fprintf(stderr, "Error: invalid thread count\n");
            return 11;
        }
    }

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
    if (shared_data) {
        shared_data->can_greet = (sem_t**)calloc(thread_count, sizeof(sem_t*));
        shared_data->thread_count = thread_count;

        for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            char semaphore_name[64];
            sprintf(semaphore_name, "/my_semaphore_%lu", (unsigned long)thread_number);

            // Check if the semaphore already exists
            shared_data->can_greet[thread_number] = sem_open(semaphore_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, !thread_number);
            if (error == (int)SEM_FAILED) {
                if (errno == EEXIST) {
                    // The semaphore already exists, you can choose to reuse it or clean it up.
                    sem_unlink(semaphore_name);
                } else {
                    fprintf(stderr, "Error: could not create named semaphore\n");
                }
                break;
            }
        }

        if (shared_data->can_greet) {
            struct timespec start_time, finish_time;
            clock_gettime(CLOCK_MONOTONIC, &start_time);

            error = create_threads(shared_data);

            clock_gettime(CLOCK_MONOTONIC, &finish_time);
            double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
                (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

            printf("Execution time: %.9lfs\n", elapsed_time);

            for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
                char semaphore_name[64];
                sprintf(semaphore_name, "/my_semaphore_%lu", (unsigned long)thread_number);
                sem_unlink(semaphore_name);
                sem_close(shared_data->can_greet[thread_number]);
            }
            free(shared_data->can_greet);
        } else {
            fprintf(stderr, "Error: could not allocate semaphores\n");
            error = 13;
        }
        free(shared_data);
    } else {
        fprintf(stderr, "Error: could not allocate shared data\n");
        error = 12;
    }
    return error;
}

int create_threads(shared_data_t* shared_data) {
    int error = EXIT_SUCCESS;
    // for thread_number = 0 to thread_count do.
    pthread_t* threads = (pthread_t*)malloc(shared_data->thread_count * sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)calloc(shared_data->thread_count, sizeof(private_data_t));
    if (threads && private_data) {
        for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            if (error == EXIT_SUCCESS) {
                private_data[thread_number].thread_number = thread_number;
                private_data[thread_number].shared_data = shared_data;
                // create_thread(greet, thread_number).
                error = pthread_create(&threads[thread_number], /*attr*/ NULL, greet, /*arg*/ &private_data[thread_number]);
                if (error == EXIT_SUCCESS) {
                  printf("Thread %d created\n", (int)thread_number);
                } else {
                    fprintf(stderr, "Error: could not create secondary thread\n");
                    error = 21;
                    break;
                }
            } else {
                fprintf(stderr, "Error: could not init semaphore\n");
                error = 22;
                break;
            }
        }

        // print "Hello from main thread"
        printf("Hello from main thread\n");

        for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            pthread_join(threads[thread_number], /*value_ptr*/ NULL);
        }

        printf("All threads joined\n");

        free(private_data);
        free(threads);
    } else {
        fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n", shared_data->thread_count);
        error = 23;
    }

    return error;
}

// procedure greet:
void* greet(void* data) {
    assert(data);
    private_data_t* private_data = (private_data_t*)data;
    shared_data_t* shared_data = private_data->shared_data;
    printf("Thread %" PRIu64 " created\n", private_data->thread_number);

    // wait(can_greet[thread_number]).
    int error = sem_wait(shared_data->can_greet[private_data->thread_number]);
    if (error) {
        fprintf(stderr, "error: could not wait for semaphore\n");
    }

    // print "Hello from secondary thread"
    printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n", private_data->thread_number, shared_data->thread_count);

    // signal(can_greet[(thread_number + 1) mod thread_count]).
    const uint64_t next_thread = (private_data->thread_number + 1)
        % shared_data->thread_count;

    error = sem_post(shared_data->can_greet[next_thread]);
    if (error) {
        fprintf(stderr, "error: could not increment semaphore\n");
    }

    return NULL;
}  // end procedure.
