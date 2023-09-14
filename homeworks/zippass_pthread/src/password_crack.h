#pragma once

#include <stdio.h>

extern int factor;
extern int paths_size;
extern int chars_size;
extern int maxLen; // Maximum password length.
extern char *chars; // chars by the input.
extern char **paths; // paths of the zip files.

// Private thread memory.
typedef struct {
    // temp zip.
    char* temp_zip_path;
    // other args.
    char* chars;
    int max_length;
    char* dir;
    int thread_id;
    int num_threads;
} thread_args;

int open_file(char* dir, char* pass);

void static_mapping(int *min, int *max, int thread_num, unsigned long long workload);

// The find_password function modified to allow threads to access it.
void* find_password_parallel(void* data);