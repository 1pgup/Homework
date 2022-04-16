#include <stdio.h>
#include <stdbool.h>

#include "cjson.h"

#define ERROR_NULL_PTR (-1)
#define ERROR_SMTH_WRONG  (-2)

// check

/*printf("%s\n", from);
printf("%s\n", to);
printf("%s\n", date);
printf("%d\n\n", content_type_is_found);
printf("%d\n\n", multipart_is_found);
printf("%s\n\n", boundary);
printf("%d\n\n", count_of_boundaries);*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return ERROR_SMTH_WRONG;
    }

    char *s = argv[1];
    if (!s) {
        return ERROR_NULL_PTR;
    }

    char from[1000] = {0};
    char to[1000] = {0};
    char date[1000] = {0};
    char boundary[1000] = {0};

    // From
    if (get_from(s, from) == ERROR_NULL_PTR) {
        return ERROR_SMTH_WRONG;
    }

    // To
    if (get_to(s, to) == ERROR_NULL_PTR) {
        return ERROR_SMTH_WRONG;
    }

    //  Date
    if (get_date(s, date) == ERROR_NULL_PTR) {
        return ERROR_SMTH_WRONG;
    }

    //  Conten-Type
    int content_type_is_found = is_content_type_found(s);
    if (content_type_is_found == ERROR_NULL_PTR) {
        return ERROR_SMTH_WRONG;
    }

    //   multipart
    int multipart_is_found = is_multipart(s, content_type_is_found);
    if (multipart_is_found == ERROR_NULL_PTR) {
        return ERROR_SMTH_WRONG;
    }

    //  boundary
    int count_of_boundaries = get_boundary(s, boundary, multipart_is_found);

    //  parts
    int parts = get_parts(content_type_is_found, multipart_is_found, count_of_boundaries);

    printf("%s|%s|%s|%d", from, to, date, parts);

    return 0;
}
