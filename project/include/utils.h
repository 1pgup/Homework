#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#include "custom_types.h"

#define CHANGING_OF_THE_CREDIT_LIMIT_FILE  "credit_limit_change.dat"
#define RECORD_FILE                        "record.dat"
#define TRANSACTION_FILE                   "transaction.dat"


#define EPS                                    1e-7

#define ERROR_WRONG_VALUE_OF_INPUT_RETURN      (-1)
#define ERROR_NULL_PTR                         (-2)

int credit_limit_change(FILE *rec_ptr, FILE *trans_ptr, FILE *cr_lim_ch_ptr, data_t client, data_t transfer);

int client_inf_write(FILE *rec_ptr, data_t client);

int transaction_write(FILE *trans_ptr, data_t transfer);

int print_in_rec_file(FILE *rec_ptr, data_t client);

int print_in_trans_file(FILE *trans_ptr, data_t transfer);


#endif  //  PROJECT_INCLUDE_UTILS_H_
