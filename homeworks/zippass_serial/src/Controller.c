#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>

#include "Controller.h"

int factor = 10;
int paths_size = 50;
int chars_size = 100;
int maxLen; // Maximum password length.
char *chars = NULL; // chars by the input.
char **paths = NULL; // paths of the zip files.

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

int open_file(char* dir, char* pass){
    int res = 0;
    const char* password = pass;
    const char* directory = dir;

    // Open the zip archive using zip_open.
    struct zip* zipArchive = zip_open(directory, ZIP_RDONLY, NULL);
    if (zipArchive == NULL) {
        printf("Could not open zip.\n");
        res = 2;
    }

    // Gets the number of entries in the zip.
    zip_int64_t numEntries = zip_get_num_entries(zipArchive, 0);
    if (numEntries < 0) {
        printf("Entries number not valid.\n");
        zip_close(zipArchive);
        res = 2;
    }

    // File index. Using the first file.
    zip_int64_t i = 0;
    
    // Try to extract one of the files using the given password.
    // Note: The NULL parameter in zip_fopen_encrypted indicates no extra encryption data.
    struct zip_file* entry = zip_fopen_encrypted(zipArchive, "file_01.txt", NULL, password);

    // Check if the password was correct.
    if (entry != NULL) {
        printf("Password is valid.\n");
        res = 0;
        // Remember to close the opened entry.
        zip_fclose(entry);
    } else {
        printf("Password is invalid.\n");
        res = 1;
    }
    
    // Close the zip archive.
    zip_close(zipArchive);

    return res;
}

void find_password(char* chars, int max_length, char* initial_password, char* dir){
    int i = 0;
    while (i < 20) {
        char* password = (char*)malloc((max_length) * sizeof(char));
        strcpy(password, initial_password);

        int of = open_file(dir, password);
        if (of == 0) {
            char *temp_dir = (char *)malloc(strlen(dir) + strlen(" ") + strlen(password) + 1);
            strcpy(temp_dir, dir);
            strcat(temp_dir, " ");
            strcat(temp_dir, password);
            free(dir);
            dir = temp_dir;
            free(password);
            return;
        } else {
            printf("%s\n", "HH");
        }
        
        free(password);
        i++;
    }
}


/*
void find_passwords(){
    // cycle through all the zip dirs and apply the find_pass() func.
    int i = 0;
    while(i < paths_size && paths[i][0] != '\0'){
        find_pass(paths[i]);
        i++;
    }
}
*/

void print_data(){
    int i = 0;
    while(i < paths_size && paths[i][0] != '\0'){
        printf("%d: %s\n" , i, paths[i]);
        i++;
    }
}

void run(int argc, char* argv[]){
    //Init vars.
    init();
    // run func.
    read_data(argc, argv);
    // test passwords
    char* password = "84520";
    //find_password(chars, maxLen, password, paths[1]);
    // print the data to the output.
    printf("%s\n", paths[1]);
    printf("%s\n", password);
    int i = open_file(paths[1], password);

    printf("i: %d\n", i);
    print_data();
    
    // Free memory.
    free_memo();
}