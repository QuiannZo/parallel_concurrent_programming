#pragma once

extern int maxLen; // Maximum password length.
extern char chars[100]; // chars by the input.
extern char paths[20][256]; // paths of the zip files.

// Reads data from the file given by the user.
void read_data(int argc, char* argv[]);
// This function tries to open the file and returns a value. If the file
// could be opened it returns 0;
int open_file(char dir[256], char password[maxLen]);
// Function to find the password using brute force.
// Recieves a dir of a zipfile and prints the file and password (if any is found).
void find_pass();
// Uses find_pass to find the passwords of all available zip files.
void find_passwords();
// Prints the output specified in the instructions.
void print_data();
// Function to run all other functions.
void run(int argc, char* argv[]);