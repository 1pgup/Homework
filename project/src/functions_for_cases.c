#include <stdio.h>

#include "custom_types.h"
#include "functions_for_cases.h"
#include "utils.h"

int writing_changes(data_t client_data, data_t transfer_data) {
    FILE *record_ptr = fopen(RECORD_FILE, "r");
    if (record_ptr == NULL) {
        return ERROR_WRONG_PTR;
    }

    FILE *trans_ptr = fopen(TRANSACTION_FILE, "r");
    if (trans_ptr == NULL) {
        fclose(record_ptr);
        return ERROR_WRONG_PTR;
    }

    FILE *limit_change_ptr = fopen(CHANGING_OF_THE_CREDIT_LIMIT_FILE, "r+");
    if (limit_change_ptr == NULL) {
        fclose(record_ptr);
        record_ptr = NULL;

        fclose(trans_ptr);
        trans_ptr = NULL;
        return ERROR_WRONG_PTR;
    }

    if (credit_limit_change(record_ptr,
                            trans_ptr,
                            limit_change_ptr,
                            client_data, transfer_data) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
        fclose(record_ptr);
        record_ptr = NULL;

        fclose(trans_ptr);
        trans_ptr = NULL;

        fclose(limit_change_ptr);
        limit_change_ptr = NULL;

        return ERROR_WRONG_INPUT;
    }
    if (credit_limit_change(record_ptr,
                            trans_ptr,
                            limit_change_ptr,
                            client_data, transfer_data) == ERROR_NULL_PTR) {
        fclose(record_ptr);
        record_ptr = NULL;

        fclose(trans_ptr);
        trans_ptr = NULL;

        fclose(limit_change_ptr);
        limit_change_ptr = NULL;

        return ERROR_NULL_PTR;
    }

    fclose(record_ptr);
    record_ptr = NULL;

    fclose(trans_ptr);
    trans_ptr = NULL;

    fclose(limit_change_ptr);
    limit_change_ptr = NULL;

    return 0;
}

int writing_client_data(data_t client_data) {
    FILE *record_ptr = fopen(RECORD_FILE, "r+");

    if (record_ptr == NULL) {
        return ERROR_WRONG_PTR;
    }
    if (client_inf_write(record_ptr, client_data) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
        fclose(record_ptr);
        return ERROR_WRONG_INPUT;
    }
    if (client_inf_write(record_ptr, client_data) == ERROR_NULL_PTR) {
        fclose(record_ptr);
        return ERROR_NULL_PTR;
    }

    fclose(record_ptr);
    record_ptr = NULL;

    return 0;
}

int writing_transfer_data(data_t transfer_data) {
    FILE *trans_ptr = fopen(TRANSACTION_FILE, "r+");

    if (trans_ptr == NULL) {
        return ERROR_WRONG_PTR;
    }

    if (transaction_write(trans_ptr, transfer_data) == ERROR_WRONG_VALUE_OF_INPUT_RETURN) {
        fclose(trans_ptr);
        trans_ptr = NULL;
        return ERROR_WRONG_INPUT;
    }
    if (transaction_write(trans_ptr, transfer_data) == ERROR_NULL_PTR) {
        fclose(trans_ptr);
        trans_ptr = NULL;
        return ERROR_NULL_PTR;
    }

    fclose(trans_ptr);
    trans_ptr = NULL;

    return 0;
}
