#include <stdio.h>

#include "utils.h"

size_t timer_from(int initial_number) {
    size_t counter = 0;
    if (initial_number < 1) {
        return counter;
    }

    for (int i = initial_number; ; --i) {
        ++counter;
        if (i == 0) {
            printf("%d\n", i);
            break;
        }
    printf("%d ", i);
    }

    return counter;
}

int custom_pow(int base, int power) {
    if (((base == 0) && (power == 0)) || (power < 0)) {
        return ERR_WRONG_VALUES_INPUT_RETURN;
    }

    int result = 1;
    for (int i = 1; i <= power; i++) {
        result *= base;
    }

    return result;
}
