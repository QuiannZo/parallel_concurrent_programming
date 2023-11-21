#pragma once

/**
 * @file common.h
 * @brief Header file. Common functions.
 */

/**
 * @brief returns a base multiplied by itself exponent times.
 * @param base base of the exponent.
 * @param argv exponent of the base.
 */
double cus_pow(double base, int exponent);

/**
 * @brief Calculates the total number of combinations using charArrayLength as base and
 * maxLength as exponent.
 * @param charArrayLength number of possible chars.
 * @param maxLength the maximum length of the password.
 */
unsigned long long calculate_total_combinations(int charArrayLength, int maxLength);

/**
 * @brief Returns the minimum value, and if there is none, the first number.
 * @param first first integer to compare.
 * @param second second integer to compare.
 */
int min_val(int first, int second);