#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cjson.h"

#define ERROR_NULL_PTR             (-1)
#define ERROR_WRONG_VALUE_OF_ARGS  (-2)

int main(int argc, const char **argv) {
    if (argc != 2) {
        return ERROR_WRONG_VALUE_OF_ARGS;
    }

    const char *path_to_eml = argv[1];
    if (!path_to_eml) {
        return ERROR_NULL_PTR;
    }

    // From
    char from[MAX_SIZE_OF_FROM] = {0};
    if (get_from(path_to_eml, from)) {
        printf("Something went wrong");
    }

    // To
    char to[MAX_SIZE_OF_TO] = {0};
    if (get_to(path_to_eml, to)) {
        printf("Something went wrong");
    }
    // Date
    char date[MAX_SIZE_OF_DATE] = {0};
    if (get_date(path_to_eml, date)) {
        printf("Something went wrong");
    }

    // parts
    int parts = get_parts(path_to_eml);
    if (parts < 0) {
        printf("Something went wrong");
    }

    printf("%s|%s|%s|%d\n", from, to, date, parts);

    return 0;
}
