#include <stddef.h>
#include <stdlib.h>

#include "test_module.h"
#include "utils.h"

#define CLIENT_DATA            1
#define TRANSACTION_DATA       2
#define BASE_UPDATE            3

#define ERROR_TEST_FAILED     (-1)
#define ERROR_WRONG_INP       (-2)
#define ERROR_WRONG_PTR_VALUE (-3)
#define ERROR_WRONG_FLAG      (-4)


int main(void) {
    int choice = 0;

    FILE *record_ptr = NULL;
    FILE *trans_ptr = NULL;
    FILE *limit_change_ptr = NULL;

    Data_t client_data, transfer;

    client_data.number = 0;
    client_data.indebtedness = 0;
    client_data.credit_limit = 0;
    client_data.cash_payments = 0;
    for (int i = 0; i < NameSize; i++) {
        client_data.name[i] = 0;
    }
    for (int i = 0; i < SurnameSize; i++) {
        client_data.surname[i] = 0;
    }
    for (int i = 0; i < AddressSize; i++) {
        client_data.address[i] = 0;
    }
    for (int i = 0; i < TelNumberSize; i++) {
        client_data.tel_number[i] = 0;
    }

    transfer.number = 0;
    transfer.indebtedness = 0;
    transfer.credit_limit = 0;
    transfer.cash_payments = 0;
    for (int i = 0; i < NameSize; i++) {
        transfer.name[i] = 0;
    }
    for (int i = 0; i < SurnameSize; i++) {
        transfer.surname[i] = 0;
    }
    for (int i = 0; i < AddressSize; i++) {
        transfer.address[i] = 0;
    }
    for (int i = 0; i < TelNumberSize; i++) {
        transfer.tel_number[i] = 0;
    }

    input_prompt();

    int read_values = 0;
    while ((read_values = scanf("%d", &choice)) != -1) {
        if (read_values != 1) {
            return ERROR_WRONG_INP;
        }
        switch (choice) {
            case CLIENT_DATA:
                record_ptr = fopen(RECORD_FILE, "r+");

                if (record_ptr == NULL) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }

                if (client_inf_write(record_ptr, client_data) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
                    return ERROR_WRONG_INP;
                }

                if (!test_read_from_rec_file(record_ptr, client_data)) {
                    return ERROR_TEST_FAILED;
                }

                fclose(record_ptr);
                record_ptr = NULL;

                break;
            case TRANSACTION_DATA:
                trans_ptr = fopen(TRANSACTION_FILE, "r+");

                if (trans_ptr == NULL) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }

                if (transaction_write(trans_ptr, transfer) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
                    return ERROR_WRONG_INP;
                }

                if (!test_read_from_trans_file(trans_ptr, transfer)) {
                    return ERROR_TEST_FAILED;
                }

                fclose(trans_ptr);
                trans_ptr = NULL;

                break;
            case BASE_UPDATE:
                record_ptr = fopen(RECORD_FILE, "r");
                trans_ptr = fopen(TRANSACTION_FILE, "r");
                limit_change_ptr = fopen(CHANGING_OF_THE_CREDIT_LIMIT_FILE, "r+");

                if ((record_ptr == NULL) || (trans_ptr == NULL) || (limit_change_ptr == NULL)) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }

                if (credit_limit_change(record_ptr,
                                        trans_ptr,
                                        limit_change_ptr,
                                        client_data, transfer) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
                    return ERROR_WRONG_INP;
                }

                if (!test_read_from_rec_file(limit_change_ptr, client_data)) {
                    return ERROR_TEST_FAILED;
                }

                fclose(record_ptr);
                record_ptr = NULL;

                fclose(trans_ptr);
                trans_ptr = NULL;

                fclose(limit_change_ptr);
                limit_change_ptr = NULL;

                break;
            default:
                puts("error");
                return ERROR_WRONG_FLAG;
        }
        input_prompt();
    }
    return 0;
}
