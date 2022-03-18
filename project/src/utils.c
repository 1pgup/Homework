#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    if (from < 1) {
        return counter;
    }
    for (int i = from; ; --i) {
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
        return 2147483647;
    }
    int result = 1;
    for (int i = 1; i <= power; i++) {
        result *= base;
    }
    return result;
}

