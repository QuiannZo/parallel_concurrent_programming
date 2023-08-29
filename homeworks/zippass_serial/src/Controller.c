#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>

#include "Controller.h"

int maxLen; // Maximum password length.
char chars[100] = {0}; // chars by the input.
char paths[20][256]; // paths of the zip files.

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

    printf("%c\n" ,chars[40]);
    printf("%d\n" ,maxLen);
    printf("%s\n" ,paths[0]);

    int i = 0;
    while(!(strcmp(paths[i], ""))){
        printf("%s\n" ,paths[i]);
        i++;
    }
}

// String?
void find_pass(){
    // Cycle through the possible combinations to find the password.
}

void find_passwords(){

}

void print_data(){

}

void run(int argc, char* argv[]){
    readData(argc, argv);
    // the other functions.
}