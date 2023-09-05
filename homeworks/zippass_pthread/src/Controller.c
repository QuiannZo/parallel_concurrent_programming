#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <zip.h>
#include <pthread.h>

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
    printf("Password: %s\n", pass);
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

double cus_pow(double base, int exponent) {
    double result = 1.0;

    if (exponent < 0) {
        base = 1.0 / base;
        exponent = -exponent;
    }

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

unsigned long long calculateCombinations(int charArrayLength, int maxLength) {
    unsigned long long combinations = 0;

    if (maxLength > 0) {
        for (int length = 1; length <= maxLength; length++) {
            combinations += cus_pow(charArrayLength, length);
        }
    }

    return combinations;
}

// Correction. Iterative version. Faster and easier than the recursive.
/*
void find_password(char* chars, int max_length, char* dir) {
    char password[max_length + 1]; // +1 for the null-terminator
    int length;
    for (length = 1; length <= max_length; length++) {
        int index[length];
        memset(index, 0, sizeof(index)); // Initialize index array

        while (1) {
            // Generate the password for the current combination of indices
            for (int i = 0; i < length; i++) {
                password[i] = chars[index[i]];
            }
            password[length] = '\0';

            int of = open_file(dir, password);
            if (of == 0) {
                strcat(dir, " ");
                strcat(dir, password);
            }

            // Increment indices
            int i;
            for (i = length - 1; i >= 0; i--) {
                if (index[i] < strlen(chars) - 1) {
                    index[i]++;
                    break;
                } else {
                    index[i] = 0;
                }
            }

            if (i < 0) {
                break; // All indices have reached their maximum, exit loop
            }
        }
    }
}*/

void find_password(char* chars, int max_length, char* dir) {
    int char_set_length = strlen(chars);
    
    for (int length = 1; length <= max_length; ++length) { // Iterar a través de las longitudes.
        for (int i = 0; i < custom_pow(char_set_length, length); ++i) { // Iterar a través de las combinaciones de caracteres.
            int num = i;
            char password[length + 1]; // +1 para el carácter nulo al final de la cadena.
            
            for (int j = 0; j < length; ++j) { // Construir la contraseña en base al número actual.
                int index = num % char_set_length;
                password[j] = chars[index];
                num /= char_set_length;
            }
            
            password[length] = '\0'; // Agregar el carácter nulo al final de la contraseña.
            
            // Aquí puedes hacer lo que necesites con la contraseña generada, como imprimir o verificar.
            printf("%s\n", password);
        }
    }
}

void find_passwords(){
    // cycle through all the zip dirs and apply the find_pass() func.
    int i = 0;
    while(i < paths_size && paths[i][0] != '\0'){
        find_password(chars, maxLen, paths[i]);
        i++;
    }
}

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
    char* password = (char*)malloc((maxLen + 1) * sizeof(char)); // +1 for null-termination
    if (password != NULL) {
        memset(password, 0, maxLen + 1); // Initialize the password buffer with null characters
    }
    find_passwords();

    // print the data to the output.
    print_data();
    
    // Free memory.
    free_memo();
    free(password);
}
