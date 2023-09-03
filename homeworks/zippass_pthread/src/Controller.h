#pragma once

/**
 * @file Controller.h
 * @brief Header file.
 */

/**
 * @brief Initializes the memory for chars and paths.
 */
void init();

/**
 * @brief Refactors path if the file has more than 50.
 */
void refactor_arr();

/**
 * @brief Refactors chars if the file provides more than 100.
 */
void refactor_chars();

/**
 * @brief Frees the memory used by chars and paths.
 */
void free_memo();

/**
 * @brief Reads data from the file provided by the user in the console. It also controlls the resizing of
 * chars and paths.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 */
void read_data(int argc, char* argv[]);

/**
 * @brief Opens a zip file and checks if the password is correct.
 * @param dir The dir of the zip file.
 * @param pass Password string.
 * @return 0: if the content verification is successful. 1: if verification fails. 2: if an errors appears.
 */
int open_file(char* dir, char* pass);

/**
 * @brief Function to find the password using brute force.
 * @param chars Chars array.
 * @param max_length The maximum length of the password.
 * @param password The current password being tested.
 * @param index The current index in the iteration.
 * @param dir The path of the zip file.
 */
void find_password(char* chars, int max_length, char* password, int start_index, int end_index, char* dir);


/**
 * @brief Prints the data to the output.
 */
void print_data();

//
void execute_p();

//
void* thread_find_password(void* data);

/**
 * @brief Runs all functions of the program.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 */
void run(int argc, char* argv[]);