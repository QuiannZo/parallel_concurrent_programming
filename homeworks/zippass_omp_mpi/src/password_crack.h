#pragma once


#include <stdio.h>

/**
 * @file password_crack.h
 * @brief Header file. Password cracker functions.
 */

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

/**
 * @brief Opens a zip file and checks if the password is correct.
 * @param dir The dir of the zip file.
 * @param pass Password string.
 * @return 0: if the content verification is successful. 1: if verification fails. 2: if an errors appears.
 */
int open_file(char* dir, char* pass);

/**
 * @brief Takes a thread id and calculates its range of work based on the workload and the total number
 * of threads. The formula was taken from the Jeisson website.
 * @param min The int that stores the minimum value in the range.
 * @param max The int that stores the maximum value in the range.
 * @param thread_num the total number of threads.
 * @param workload the total workload for the password length.
 */
void static_mapping(int *min, int *max, int thread_num, unsigned long long workload);

// The find_password function modified to allow threads to access it.
/**
 * @brief The find_password function modified to allow threads to access it. The algorithm is
 * serial now so the workload is divisible.
 * @param data the private data of the thread.
 */
void find_password_parallel(char* chars, int max_length, char* dir);