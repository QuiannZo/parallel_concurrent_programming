#include <stdio.h>

#include "common.h"

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

unsigned long long calculate_total_combinations(int charArrayLength, int maxLength) {
    unsigned long long combinations = 0;

    if (maxLength > 0) {
        for (int length = 1; length <= maxLength; length++) {
            combinations += cus_pow(charArrayLength, length);
        }
    }

    return combinations;
}

int min_val(int first, int second){
    if(first < second){
        return first;
    } else if(second < first){
        return second;
    }
    return first;
}