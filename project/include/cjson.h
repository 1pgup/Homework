#ifndef PROJECT_INCLUDE_CJSON_H_
#define PROJECT_INCLUDE_CJSON_H_

#include <stdbool.h>

#define ERROR_NULL_PTR (-1)

int is_content_type_found(char* filename);
int is_multipart(char* filename, int content_type_is_found);

int get_boundary(char* filename, char *boundary, int multipart_is_found);
int get_parts(int is_content_type, int is_multipart, int count_of_boundaries);

int get_date(char* filename, char *date);
int get_from(char* filename, char* from);
int get_to(char* filename, char* to);


#endif  // PROJECT_INCLUDE_CJSON_H_
