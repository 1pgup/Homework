#include "fromOnetoN.h"

void fromOneToNumGreaterThanOne(int number) {
    if (number > 1) {
		fromOneToNumGreaterThanOne(number - 1);
		printf(" %i", number);
	} else {
		printf("%i", number);
	}
}
void fromOneToNumLessThanOne(int number) {
    if (number < 1) {
        fromOneToNumLessThanOne(number + 1);
        printf(" %i", number);
    } else {
        printf("%i", number);
    }
}
