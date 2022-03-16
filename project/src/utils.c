#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    if (from > 0) {
        for (int i = from; ; --i) {
            ++counter;
            if (i == 0) {
                printf("%d\n", i);
                break;
            }
        printf("%d ", i);
        }
    }
    return counter;
}

int custom_pow(int base, unsigned int power) {
    int result = 1;
    for (unsigned int i = 1; i <= power; i++)
        result *= base;
    return result;
}

