#include <stdlib.h>

#include "from_one_to_n.h"
#include "is_prime.h"
#include "utils.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG  (-2)
#define ERR_WRONG_INP  (-3)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_FOO_REC     4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char *endptr;
    int test_case = (int) strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return ERR_WRONG_INP;
    }
        const char* data;
        data = argv[2];

        switch (test_case) {
            case TST_FOO_FIX: {
                if (argc == 3) {
                    int to = (int) strtol(data, &endptr, 10);
                    if (*endptr == '\0') {
                        printf("%zu\n", timer_from(to));
                    } else {
                        return ERR_WRONG_INP;
                    }
                } else {
                    return ERR_ARGS_COUNT;
                }
                break;
            }
            case TST_FOO_IMPL: {
                if (argc == 4) {
                    if (!((((int) strtol(argv[3], &endptr, 10) < 0) && (*endptr != '\0'))
                            || ((((int) strtol(data, &endptr, 10) == 0) && (*endptr != '\0'))
                                && (((int) strtol(argv[3], &endptr, 10) == 0) && (*endptr != '\0'))))) {
                        int base = strtol(data, &endptr, 10);
                        unsigned int pow =  strtol(argv[3], &endptr, 10);
                        int res = custom_pow(base, pow);

                        printf("%d\n", res);
                    } else {
                        return ERR_WRONG_INP;
                    }
                } else {
                    return ERR_ARGS_COUNT;
                }
                break;
            }
            case TST_MOD_IMPL: {
                if (argc == 3) {
                    int num = (int) strtol(data, &endptr, 10);
                    if (*endptr == '\0') {
                        printf("%d\n", is_prime(num));
                    } else {
                        return ERR_WRONG_INP;
                    }
                } else {
                    return ERR_ARGS_COUNT;
                }
                break;
            }
            case TST_FOO_REC: {
                if (argc == 3) {
                    int number = (int) strtol(data, &endptr, 10);
                    if (*endptr == '\0') {
                        from_one_to_n(number);
                        printf("\n");
                    } else {
                        return ERR_WRONG_INP;
                    }
                } else {
                    return ERR_ARGS_COUNT;
                }
                break;
            }
            default: {
                return ERR_WRONG_FLG;
            }
        }
}
