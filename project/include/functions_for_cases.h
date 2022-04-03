#ifndef PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_
#define PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_

#include "custom_types.h"
#include "utils.h"

#define ERROR_WRONG_PTR         (-1)
#define ERROR_WRONG_INPUT       (-2)

int writing_changes(data_t client_data, data_t transfer_data);

int writing_client_data(data_t client_data);

int writing_transfer_data(data_t transfer_data);

#endif  //  PROJECT_INCLUDE_FUNCTIONS_FOR_CASES_H_
