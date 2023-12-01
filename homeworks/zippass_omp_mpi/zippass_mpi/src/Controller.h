#pragma once

#include "queue.h"

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
 * @brief Prints the data to the output.
 */
void print_data();

/**
 * @brief Runs all functions of the program.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 */
void run(int argc, char* argv[]);

// Function to process files on parallel.
void process_files_parallel(Queue* fileQueue);