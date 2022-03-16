#include "is_prime.h"

int is_prime(int number) {
    int key = 1;
    if (number <= 1)
        key = 0;
    if (key) {
        for (int i = 2; i <= (number/2) ; i++) {
            if (number % i == 0)
                key = 0;
        }
    }
    return key;
}
