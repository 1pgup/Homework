#ifndef PROJECT_INCLUDE_TEST_MODULE_H_
#define PROJECT_INCLUDE_TEST_MODULE_H_

#include <string.h>

#include "utils.h"

int test_read_from_rec_file(FILE *file_ptr, Data_t inputed_data);

int test_read_from_trans_file(FILE *file_ptr, Data_t inputed_data);

int read_from_rec_file(FILE *file_ptr, Data_t got_data);

int read_from_trans_file(FILE *file_ptr, Data_t got_data);

#endif  //  PROJECT_INCLUDE_TEST_MODULE_H_
