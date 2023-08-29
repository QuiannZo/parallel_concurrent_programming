#pragma once

// Reads data from the file given by the user.
void read_data(int argc, char* argv[]);
// Function to find the password using brute force.
// Recieves a dir of a zipfile and prints the file and password (if any is found).
void find_pass();
// Uses find_pass to find the passwords of all available zip files.
void find_passwords();
// Prints the output specified in the instructions.
void print_data();
// Function to run all other functions.
void run(int argc, char* argv[]);