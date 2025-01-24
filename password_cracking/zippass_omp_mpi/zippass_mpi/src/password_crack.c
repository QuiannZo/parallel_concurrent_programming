#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

#include "password_crack.h"
#include "common.h"

int factor = 10;
int paths_size = 50;
int chars_size = 100;
int maxLen; // Maximum password length.
char *chars = NULL; // chars by the input.
char **paths = NULL; // paths of the zip files.

int open_file(char* dir, char* pass){
    int res = 0;
    const char* password = pass;
    const char* directory = dir;

    // Open the zip archive using zip_open.
    struct zip* zipArchive = zip_open(directory, ZIP_RDONLY, NULL);
    if (zipArchive == NULL) {
        return 2;
    }

    // Gets the number of entries in the zip.
    zip_int64_t numEntries = zip_get_num_entries(zipArchive, 0);
    if (numEntries < 0) {
        zip_close(zipArchive);
        return 2;
    }

    // File index. Using the first file.
    zip_int64_t i = 0;

    // Extract and check the file using the given password.
    struct zip_file* entry = zip_fopen_index_encrypted(zipArchive, i, NULL, password);

    // Check if the password was correct.
    if (entry != NULL) {
        char buffer[256];
        ssize_t bytesRead = zip_fread(entry, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            const char* expectedContent = "CI0117-23a";
            // Compare the content with the expected content.
            if (strstr(buffer, expectedContent) != NULL) {
                //printf("Content verification successful.\n");
                res = 0;
            } else {
                //printf("Content verification failed.\n");
                res = 1;
            }
        }
        zip_fclose(entry);
    } else {
        res = 1;
    }

    // Close the zip archive.
    zip_close(zipArchive);

    return res;
}

// The find_password function modified to allow threads to access it.
void find_password_parallel(char* chars, int max_length, char* dir) {
    char temp[256];
    strcat(temp, dir);
    int char_set_length = strlen(chars);
    for (int length = 1; length <= max_length; ++length) {
        // Calculate the total combinations outside the loop to avoid race conditions
        int total_combinations = calculate_total_combinations(char_set_length, length);

        //#pragma omp parallel for schedule(dynamic) shared(chars, max_length, dir, char_set_length)
        for (int i = 0; i < total_combinations; ++i) {
            int num = i;
            char password[length + 1];

            // cambio de base.
            for (int j = 0; j < length; ++j) {
                int index = num % char_set_length;
                password[j] = chars[index];
                num /= char_set_length;
            }

            password[length] = '\0';

            // Make sure you pass the correct arguments to open_file
            int of = open_file(dir, password);

            //#pragma omp critical
            {
                if (of == 0) {
                    strcat(temp, " ");
                    strcat(temp, password);
                }
            }
        }
    }
    printf("%s\n", temp);
}