#ifndef PROJECT_INCLUDE_TEST_MODULE_H_
#define PROJECT_INCLUDE_TEST_MODULE_H_

#include <stdio.h>

#include "custom_types.h"

#define ERROR_WRONG_VALUE_OF_INPUT_RETURN      (-1)
#define ERROR_WRONG_VALUE_OF_PTR               (-2)
#define ERROR_TEST_FAILED                      (-3)
#define ERROR_DATA_MISMATCHES                  (-4)

int check_test_rec_or_cr_limit_change(FILE* test_ptr);
int check_test_trans(FILE* test_ptr);
int test_rec_or_cr_limit_change_file(FILE* test_ptr);
int test_trans_file(FILE* test_ptr);

#endif  //  PROJECT_INCLUDE_TEST_MODULE_H_
