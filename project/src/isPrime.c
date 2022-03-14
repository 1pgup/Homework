#include "isPrime.h"

int isPrime(int number) {
    int key = 1;
    if (number <= 1) {
        key = 0;
    } else {
        for (int i = 2; i < number; i++) {
            if (number % i == 0)
                key = 0;
        }
    }
    return key;
}
