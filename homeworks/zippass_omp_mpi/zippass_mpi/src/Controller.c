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
#include <mpi.h>
#include <queue.h>

#include "password_crack.h"

#define QUEUE_SIZE 100

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

void read_data(){
    char* filename;
    // Read from input.
    printf("Enter text:\n");

    int c = 0;
    int character = 0;
    while ((character = getchar()) != EOF && character != '\n') {
        if (c == (chars_size - 1)) {
            refactor_chars();
        }
        chars[c] = character;
        c++;
    }
    chars[c] = '\0';

    // get the max length.
    scanf("%d\n\n", &maxLen);

    // get the file paths.
    int str_counter = 0;
    bool end_of_input = false;
    while (!end_of_input) {
        if (fgets(paths[str_counter], 256, stdin) != NULL) {
            // Quit the '\n' at the end of the lines to avoid errors
            int len = strlen(paths[str_counter]);
            if ((len > 0 && paths[str_counter][len - 1] == '\n') || paths[str_counter][len - 1] == '\r') {
                paths[str_counter][len - 1] = '\0'; // Replace '\n' with '\0'
            }

            // Check if the line is empty (only contains a newline character)
            if (len == 1 || len == 0) {
                end_of_input = true; // Exit the loop if an empty line is encountered
            } else {
                if ((str_counter - 1) == paths_size) {
                    refactor_arr();
                }
                str_counter++;
            }
        } else {
            end_of_input = true; // Reached the end of input stream
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

// Function to process files on parallel.
void process_files_parallel(Queue* fileQueue) {
    int rank, size;
    char filename[256];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cada proceso MPI procesa un archivo a la vez.
    while (!is_queue_empty(fileQueue)) {
        // Desencola un archivo para procesar
        char* filepath = dequeue(fileQueue);

        // El proceso 0 (maestro) envía el archivo a los otros procesos
        if (rank == 0) {
            for (int dest = 1; dest < size; dest++) {
                MPI_Send(filepath, 256, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
            }
        } else {
            // Los procesos esclavos reciben el nombre del archivo.
            MPI_Recv(filename, 256, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Cada proceso hace su trabajo.
            find_password_parallel(chars, maxLen, filename);
        }
    }
}

void run(int argc, char* argv[]){
    //Init vars.
    init();

    // run func.
    read_data();

    // // test passwords. Using MPI.
    MPI_Init(&argc, &argv);

    Queue fileQueue;
    initialize_queue(&fileQueue);

    int rank = 0;
    if (rank == 0) {
        // El proceso 0 llena la cola con los nombres de los archivos.
        for (int k = 0; k < paths_size && paths[k][0] != '\0'; k++) {
            enqueue(&fileQueue, paths[k]);
        }
    }

    // Every process works on its file.
    process_files_parallel(&fileQueue);

    // Finalize.
    MPI_Finalize();

    // print the data to the output.
    print_data();
    
    // Free memory.
    free_memo();
}
