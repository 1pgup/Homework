#ifndef PROJECT_INCLUDE_TEST_MODULE_H_
#define PROJECT_INCLUDE_TEST_MODULE_H_

#include <stdio.h>

#include "custom_types.h"

#define ERROR_WRONG_VALUE_OF_PTR               (-5)
#define ERROR_TEST_FAILED                      (-6)

#define EPS  1e-7

int check_test_rec_or_cr_limit_change(char* filename);
int check_test_trans(char* filename);
int test_rec_or_cr_limit_change_file(FILE* test_ptr);
int test_trans_file(FILE* test_ptr);

#endif  //  PROJECT_INCLUDE_TEST_MODULE_H_
