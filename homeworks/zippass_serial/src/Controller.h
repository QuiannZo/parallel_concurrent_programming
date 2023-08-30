#pragma once

extern int factor;
extern int maxLen; // Maximum password length.
extern char *chars; // chars by the input.
extern char **paths; // paths of the zip files.

// Initializes the memory.
void init();
// If needed, the array can grow to hold more zip file dirs.
void refactor_arr();
// If needed the array of chars can grow.
void refactor_chars();
// frees the memory used.
void free_memo();
// Reads data from the file given by the user.
void read_data(int argc, char* argv[]);
// This function tries to open the file and returns a value. If the file
// could be opened it returns 0;
int open_file(char* dir, char* pass);
// Function to find the password using brute force.
// Recieves a dir of a zipfile and prints the file and password (if any is found).
void find_password(char* chars, int max_length, char* password, int index, char* dir);
// Uses find_pass to find the passwords of all available zip files.
//void find_passwords();
// Prints the output specified in the instructions.
void print_data();
// Function to run all other functions.
void run(int argc, char* argv[]);