#include <stdio.h>

#include "custom_types.h"
#include "prints.h"
#include "utils.h"

int credit_limit_change(FILE *rec_ptr, FILE *trans_ptr, FILE *cr_lim_ch_ptr, data_t client, data_t transfer) {
    int amount_of_assigned_values = 0;
    while ((amount_of_assigned_values = fscanf(rec_ptr, "%d%19s%19s%29s%14s%lf%lf%lf",
                                                        &client.number,
                                                        client.name,
                                                        client.surname,
                                                        client.address,
                                                        client.tel_number,
                                                        &client.indebtedness,
                                                        &client.credit_limit,
                                                        &client.cash_payments)) != -1) {
        if (amount_of_assigned_values != 8) {
            return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
        }
        while ((amount_of_assigned_values = fscanf(trans_ptr, "%d %lf",
                                                                &transfer.number,
                                                                &transfer.cash_payments)) !=  -1) {
            if (amount_of_assigned_values !=  2) {
                return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
            }
            if ((client.number == transfer.number) && (transfer.cash_payments != 0)) {
                client.credit_limit += transfer.cash_payments;
            }
        }
    if (print_in_rec_file(cr_lim_ch_ptr, client)) {
        return ERROR_NULL_PTR;
    }
    rewind(trans_ptr);
    }
    return 0;
}

int client_inf_write(FILE *rec_ptr, data_t client) {
    print_client_inf();
    int amount_of_assigned_values = 0;
    while ((amount_of_assigned_values = scanf("%d%19s%19s%29s%14s%lf%lf%lf",
                                                &client.number,
                                                client.name,
                                                client.surname,
                                                client.address,
                                                client.tel_number,
                                                &client.indebtedness,
                                                &client.credit_limit,
                                                &client.cash_payments))!= -1) {
        if (amount_of_assigned_values != 8) {
            return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
        }
        if (print_in_rec_file(rec_ptr, client)) {
            return ERROR_NULL_PTR;
        }
        print_client_inf();
    }
    return 0;
}

int transaction_write(FILE *trans_ptr, data_t transfer) {
    print_transfer_inf();
    int amount_of_assigned_values = 0;
    while ((amount_of_assigned_values = scanf("%d%lf", &transfer.number, &transfer.cash_payments)) != -1) {
        if (amount_of_assigned_values != 2) {
            return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
        }
        if (print_in_trans_file(trans_ptr, transfer)) {
            return ERROR_NULL_PTR;
        }
        print_transfer_inf();
    }
    return 0;
}

int print_in_rec_file(FILE *rec_ptr, data_t client) {
    if (!rec_ptr) {
        return ERROR_NULL_PTR;
    }
    fprintf(rec_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                        client.number,
                        client.name,
                        client.surname,
                        client.address,
                        client.tel_number,
                        client.indebtedness,
                        client.credit_limit,
                        client.cash_payments);
    return 0;
}

int print_in_trans_file(FILE *trans_ptr, data_t transfer) {
    if (!trans_ptr) {
        return ERROR_NULL_PTR;
    }
    fprintf(trans_ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
    return 0;
}
