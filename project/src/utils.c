#include "utils.h"
#include <stdio.h>

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; ; --i) {
        ++counter;
        if (i == 0) {
            printf("%i\n", i);
            break;
        }
        printf("%i ", i);
    }
    return counter;
}

int custom_pow(int base, int power) {
    int result = 1;
    for (int i = 1; i <= power; i++)
        result *= base;
    return result;
}

