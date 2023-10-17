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
    combinations += cus_pow(charArrayLength, maxLength);
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