#ifndef PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_
#define PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_

#include "custom_types.h"

#define ERROR_WRONG_PTR               (-3)
#define ERROR_WRONG_RETURN_VALUE      (-4)

int writing_changes(data_t client_data, data_t transfer_data);

int writing_client_data(data_t client_data);

int writing_transfer_data(data_t transfer_data);

#endif  //  PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_
