#ifndef PROJECT_INCLUDE_CJSON_H_
#define PROJECT_INCLUDE_CJSON_H_

int get_date(const char* path_to_eml, char* date);
int get_from(const char* path_to_eml, char* from);
int get_parts(const char* path_to_eml);
int get_to(const char* path_to_eml, char* to);

typedef enum {
    MAX_SIZE_OF_FROM = 1000,
    MAX_SIZE_OF_TO = 1000,
    MAX_SIZE_OF_DATE = 1000,
    MAX_SIZE_OF_SECONDARY_WORD = 100
} sizes_t;

#endif  // PROJECT_INCLUDE_CJSON_H_
