#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// thread_shared_data_t
typedef struct shared_data {
  uint64_t hit_num;
  pthread_mutex_t can_access_position;
  uint64_t thread_count;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  int pinata_hits;
  shared_data_t* shared_data;
} private_data_t;

void* hit_pinata(void* data);

int main(int argc, char* argv[]){
    int error = EXIT_SUCCESS;
    uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    int hit_number;

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

    if (argc == 3) {
        if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
        } else {
            fprintf(stderr, "Error: invalid input\n");
            return 11;
        }
        if(sscanf(argv[2], "%d", &hit_number) == 1){
        } else {
            fprintf(stderr, "Error: invalid input\n");
            return 11; 
        }
    }

    shared_data->thread_count = thread_count;
    shared_data->hit_num = hit_number;

    int hits[thread_count];

    pthread_t* threads = (pthread_t*)malloc(shared_data->thread_count * sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)calloc(shared_data->thread_count, sizeof(private_data_t));

    if (threads && private_data) {
        for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            private_data[thread_number].thread_number = thread_number;
            private_data[thread_number].shared_data = shared_data;

            // create_thread(hit_pinata, thread_number)
            error = pthread_create(&threads[thread_number], /*attr*/ NULL, hit_pinata, /*arg*/ &private_data[thread_number]);
            
            if (error != EXIT_SUCCESS) {
                fprintf(stderr, "Error: could not create secondary thread\n");
                error = 21;
                break;
            }
        }

        // Join threads.
        for (uint64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            pthread_join(threads[thread_number], /*value_ptr*/ NULL);
        }

        free(private_data);
        free(threads);
    }
}

void* hit_pinata(void* data){
    private_data_t* private_data = (private_data_t*) data;
    shared_data_t* shared_data = private_data->shared_data;

    int my_position = private_data->thread_number;

    // Lock mutex.
    while(shared_data->hit_num > 0) {
        pthread_mutex_lock(&shared_data->can_access_position);
        --shared_data->hit_num;
        private_data->pinata_hits++;

        // unlock(can_access_position)
        pthread_mutex_unlock(&shared_data->can_access_position);
    }
    printf("Thread %d/%d: %d hits", my_position, shared_data->hit_num, private_data->pinata_hits);
    return;
}