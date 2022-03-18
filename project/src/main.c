#include <stdlib.h>

#include "from_one_to_n.h"
#include "is_prime.h"
#include "utils.h"

#define ERR_ARGS_COUNT     (-1)
#define ERR_WRONG_FLG      (-2)
#define ERR_WRONG_PTR      (-3)
#define ERR_WRONG_INP      (-4)

#define TST_FOO_FIX          1
#define TST_FOO_IMPL         2
#define TST_MOD_IMPL         3
#define TST_FOO_REC          4

int main(int argc, const char** argv) {
    if (argc < 3) {
        printf("Wrong amount of inputed variables\n");
        return ERR_ARGS_COUNT;
    }

    char *endptr = NULL;
    int test_case = (int) strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return ERR_WRONG_PTR;
    }
    const char* data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            if (!(argc == 3)) {
                printf("Wrong amount of inputed variables\n");
                return ERR_ARGS_COUNT;
            }
            int to = (int) strtol(data, &endptr, 10);
            if (*endptr != '\0') {
                return ERR_WRONG_PTR;
            }
            printf("%zu\n", timer_from(to));
            break;
        }
        case TST_FOO_IMPL: {
            if (!(argc == 4)) {
                printf("Wrong amount of inputed variables\n");
                return ERR_ARGS_COUNT;
            }
            int base = strtol(data, &endptr, 10);
            if (*endptr != '\0') {
                return ERR_WRONG_PTR;
            }
            int pow =  strtol(argv[3], &endptr, 10);
            if (*endptr != '\0') {
                return ERR_WRONG_PTR;
            }
            int res = custom_pow(base, pow);
            if (res == 2147483647) {
                printf("You inputed 0 0 or negative power\n");
                return ERR_WRONG_INP;
            }
            printf("%d\n", res);
            break;
        }
        case TST_MOD_IMPL: {
            if (argc > 3) {
                printf("Wrong amount of inputed variables\n");
                return ERR_ARGS_COUNT;
            }
            int num = (int) strtol(data, &endptr, 10);
            if (*endptr != '\0') {
                return ERR_WRONG_PTR;
            }
            printf("%d\n", is_prime(num));
            break;
        }
        case TST_FOO_REC: {
            if (argc != 3) {
                printf("Wrong amount of inputed variables\n");
                return ERR_ARGS_COUNT;
            }
            int number = (int) strtol(data, &endptr, 10);
            if (*endptr != '\0') {
                return ERR_WRONG_PTR;
            }
            from_one_to_n(number);
            printf("\n");
            break;
        }
        default: {
            printf("Wrong flag\n");
            return ERR_WRONG_FLG;
        }
    }
}
