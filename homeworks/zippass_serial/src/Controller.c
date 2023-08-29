#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>

#include "Controller.h"

int maxLen = 0; // Maximum password length.
char chars[100] = {0}; // chars by the input.
char paths[20][256]; // paths of the zip files.
//char output[20][256];

void read_data(int argc, char* argv[]){
    // init paths.
    for (int i = 0; i < 20; i++) {
        strcpy(paths[i], "");
    }

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

            // get the max length.
            fscanf(argument, "%d\n\n", &maxLen);

            // get the file paths.
            int str_counter = 0;
            while (fgets(paths[str_counter], sizeof(paths[str_counter]), argument) != NULL){
                // Quit the '\n' at the end of the lines to avoid errors.
                // This piece of code was gathered from chatgpt 3.5
                int len = strlen(paths[str_counter]);
                if (len > 0 && paths[str_counter][len - 1] == '\n') {
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

}

void find_pass(char dir[256]){
    // Cycle through the possible combinations to find the password.
    // Create a password string.
    char *password = (char *)malloc(maxLen * sizeof(char));
    // Fill it with the first char given in the input.
    for(int i = 0; i < maxLen; ++i){
        password[i] = chars[0];
    }
    //password = "01234";
    printf("Maxlen %d\n", maxLen);
    printf("password: %c end.\n", password[0]);
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
        printf("%s\n" ,paths[i]);
        i++;
    }
}

void run(int argc, char* argv[]){
    // run func.
    read_data(argc, argv);
    // ...
    // print the data to the output.
    find_pass(paths[0]);
    print_data();
}