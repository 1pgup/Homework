#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#include "custom_types.h"
#include "making_format_string.h"
#include "prints.h"

#define CHANGING_OF_THE_CREDIT_LIMIT_FILE  "credit_limit_change.dat"
#define RECORD_FILE                        "record.dat"
#define TRANSACTION_FILE                   "transaction.dat"

#define ERROR_WRONG_VALUE_OF_INPUT_RETURN      (-1)

int credit_limit_change(FILE *rec_ptr, FILE *trans_ptr, FILE *cr_lim_ch_ptr, Data_t client, Data_t transfer);

int client_inf_write(FILE *rec_ptr, Data_t client);

int transaction_write(FILE *trans_ptr, Data_t transfer);

void print_in_rec_file(FILE *rec_ptr, Data_t client);

void print_in_trans_file(FILE *trans_ptr, Data_t transfer);

#endif  //  PROJECT_INCLUDE_UTILS_H_
