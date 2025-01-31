#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#include "password_crack.h"
#include "queue.h"


void init(){
    // Allocate memory for chars.
    chars = (char*)malloc(chars_size * sizeof(char));
    //Allocate memory for paths.
    paths = (char**)malloc(paths_size * sizeof(char *));
    for(int i = 0; i < paths_size; ++i){
        paths[i] = (char*)malloc(256*sizeof(char));
    }
}

void refactor_arr(){
    paths = (char**)realloc(paths, (paths_size * factor) * sizeof(char *));
    for (int i = paths_size; i < (paths_size * factor); ++i) {
        paths[i] = (char*)malloc(256 * sizeof(char));
    }
    paths_size *= factor;
}

void refactor_chars(){
    chars = (char*)realloc(chars, (chars_size * factor) * sizeof(char));
    chars_size *= factor;
}

void free_memo(){
    // free the chars.
    free(chars);
    // free paths arr.
    for(int i = 0; i < paths_size; ++i){
        free(paths[i]);
    }
    free(paths);
}

void read_data(int argc, char* argv[]){
    char* filename;
    if(argc > 1){
        // If the file is a text file:
        if (strcmp(argv[1], "-f") == 0){
            filename = argv[2];
            FILE* argument = fopen(filename, "r");
            if (argument == NULL) {
                printf("Error: Could not open file '%s'\n", filename);
            }

            int c = 0;
            int character = 0;
            while((character = getc(argument)) != EOF && character != '\n'){
                if(c == (chars_size - 1)){
                    refactor_chars();
                }
                chars[c] = character;
                c++;
            }
            chars[c] = '\0';

            // get the max length.
            fscanf(argument, "%d\n\n", &maxLen);

            // get the file paths.
            int str_counter = 0;
            while (fgets(paths[str_counter], 256, argument) != NULL){
                if((str_counter - 1) == paths_size){
                    refactor_arr();
                }
                // Quit the '\n' at the end of the lines to avoid errors.
                // This piece of code was gathered from chatgpt 3.5
                int len = strlen(paths[str_counter]);
                if ((len > 0 && paths[str_counter][len - 1] == '\n') || paths[str_counter][len - 1] == '\r') {
                    paths[str_counter][len - 1] = '\0'; // Replace '\n' with '\0'
                }
                str_counter++;
            }

            // close the file.
            fclose(argument);
        }
    }
}

void print_data(){
    int i = 0;
    while(i < paths_size && paths[i][0] != '\0'){
        printf("%d: %s\n" , i, paths[i]);
        i++;
    }
}

void* producer(void* arg) {
    Queue* q = (Queue*)arg;

    // Enqueue zip file dirs.
    for (int i = 0; i < paths_size && paths[i][0] != '\0'; i++) {
        enqueue(q, paths[i]);
    }

    for (int i = 0; i < paths_size && paths[i][0] != '\0'; i++) {
        enqueue(q, NULL);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) {
    Queue* q = (Queue*)arg;

    while (!(is_queue_empty(q))) {
        char* dir = dequeue(q);

        if (dir == NULL) {
            break;
        }

        // Call find_password_parallel.
        find_password_parallel(dir);
    }
    pthread_exit(NULL);
}

void run(int argc, char* argv[]){
    //Init vars.
    init();
    // run func.
    read_data(argc, argv);

    Queue queue;
    initialize_queue(&queue);

    // // test passwords.
    uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

    // Create producer and consumer threads.
    pthread_t producer_thread;
    pthread_t consumer_threads[thread_count];

    pthread_create(&producer_thread, NULL, producer, &queue);
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, &queue);
    }

    // Join the threads.
    pthread_join(producer_thread, NULL);
    for (int i = 0; i < thread_count; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // print the data to the output.
    print_data();
    
    // Free memory.
    free_memo();
}
