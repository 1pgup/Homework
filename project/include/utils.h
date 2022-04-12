#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#include "custom_types.h"

#define CREDIT_LIMIT_FILE  "credit_limit_change.dat"
#define RECORD_FILE        "record.dat"
#define TRANSACTION_FILE   "transaction.dat"

int credit_limit_change(FILE *rec_ptr, FILE *trans_ptr, FILE *cr_lim_ch_ptr, data_t client, data_t transfer);

int client_inf_write(FILE *rec_ptr, data_t client);

int transaction_write(FILE *trans_ptr, data_t transfer);

int print_in_rec_file(FILE *rec_ptr, data_t client);

int print_in_trans_file(FILE *trans_ptr, data_t transfer);


#endif  //  PROJECT_INCLUDE_UTILS_H_
