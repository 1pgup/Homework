#ifndef PROJECT_INCLUDE_TEST_MODULE_H_
#define PROJECT_INCLUDE_TEST_MODULE_H_

#include <string.h>
#include <stdio.h>

#include "custom_types.h"
#include "making_format_string.h"

#define ERROR_WRONG_VALUE_OF_INPUT_RETURN      (-1)

int test_read_from_rec_file(FILE *file_ptr, Data_t inputed_data);

int test_read_from_trans_file(FILE *file_ptr, Data_t inputed_data);

int read_from_rec_file(FILE *file_ptr, Data_t got_data);

int read_from_trans_file(FILE *file_ptr, Data_t got_data);

#endif  //  PROJECT_INCLUDE_TEST_MODULE_H_
