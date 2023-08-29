#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>

#include "Controller.h"

int maxLen; // Maximum password length.
char *chars = NULL; // chars by the input.
char **paths = NULL; // paths of the zip files.
//char output[20][256];

void init(){
    // Allocate memory for chars.
    chars = (char*)malloc(50*sizeof(char));
    //Allocate memory for paths.
    paths = (char**)malloc(20*sizeof(char *));
    for(int i = 0; i < 20; ++i){
        paths[i] = (char*)malloc(256*sizeof(char));
    }
}

void free_memo(){
    // free the chars.
    free(chars);
    for(int i = 0; i < 20; ++i){
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
                return EXIT_FAILURE; // returns 1.
            }

            int c = 0;
            int character = 0;
            while((character = getc(argument)) != EOF && character != '\n'){
                chars[c] = character;
                c++;
            }
            chars[c] = '\0';

            // get the max length.
            fscanf(argument, "%d\n\n", &maxLen);

            // get the file paths.
            int str_counter = 0;
            while (fgets(paths[str_counter], 256, argument) != NULL){
                // Quit the '\n' at the end of the lines to avoid errors.
                // This piece of code was gathered from chatgpt 3.5
                int len = strlen(paths[str_counter]);
                if (len > 0 && paths[str_counter][len - 1] == '\n' || paths[str_counter][len - 1] == '\r') {
                    paths[str_counter][len - 1] = '\0'; // Replace '\n' with '\0'
                }
                str_counter++;
            }

            // close the file.
            fclose(argument);
        }
    }

    //printf("%d\n" ,maxLen);
    //printf("%s\n" ,paths[0]);
}

int open_file(char dir[256], char password[maxLen]){
    // Tries to open the file with the given password.
    return 0;
}

void find_pass(char dir[256]){
    // Cycle through the possible combinations to find the password.
    // Create a password string.
    char *password = (char *)malloc(maxLen * sizeof(char));
    password[maxLen] = '\0';
    // Fill it with the first char given in the input.
    for(int i = 0; i < maxLen; ++i){
        password[i] = (char)chars[4];
    }
    printf("Maxlen %d\n", maxLen);
    printf("password: %s.\n", password);
    
    //free memory.
    free(password);
}

void find_passwords(){
    // cycle through all the zip dirs and apply the find_pass() func.
    int i = 0;
    while(i < 20 && paths[i][0] != '\0'){
        find_pass(paths[i]);
        i++;
    }
}

void print_data(){
    int i = 0;
    while(i < 20 && paths[i][0] != '\0'){
        printf("%d: %s\n" , i, paths[i]);
        i++;
    }
}

void run(int argc, char* argv[]){
    //Init vars.
    init();
    // run func.
    read_data(argc, argv);
    // print the data to the output.
    find_pass(paths[0]);
    print_data();
    // Free memory.
    free_memo();
}