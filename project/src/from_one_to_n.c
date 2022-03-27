#include <stdio.h>

#include "from_one_to_n.h"

void from_one_to_n(int number) {
    if (number > 1) {
        from_one_to_n(number - 1);
    }

    if (number < 1) {
        from_one_to_n(number + 1);
    }

    if (number != 1) {
        printf(" %d", number);
    }

    if (number == 1) {
        printf("%d", number);
    }
}
