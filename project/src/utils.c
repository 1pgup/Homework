#include "utils.h"

int credit_limit_change(FILE *rec_ptr, FILE *trans_ptr, FILE *cr_lim_ch_ptr, Data_t client, Data_t transfer) {
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
    print_in_rec_file(cr_lim_ch_ptr, client);
    rewind(trans_ptr);
    }
    return 1;
}

int client_inf_write(FILE *rec_ptr, Data_t client) {
    input_prompt_client_inf();
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
        print_in_rec_file(rec_ptr, client);
        input_prompt_client_inf();
    }
    return 1;
}

void print_in_rec_file(FILE *rec_ptr, Data_t client) {
    fprintf(rec_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                        client.number,
                        client.name,
                        client.surname,
                        client.address,
                        client.tel_number,
                        client.indebtedness,
                        client.credit_limit,
                        client.cash_payments);
}
void print_in_trans_file(FILE *trans_ptr, Data_t transfer) {
    fprintf(trans_ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
}

int transaction_write(FILE *trans_ptr, Data_t transfer) {
    input_prompt_transfer_inf();
    int amount_of_assigned_values = 0;
    while ((amount_of_assigned_values = scanf("%d%lf", &transfer.number, &transfer.cash_payments)) != -1) {
        if (amount_of_assigned_values != 2) {
            return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
        }
        print_in_trans_file(trans_ptr, transfer);
        input_prompt_transfer_inf();
    }
    return 1;
}
