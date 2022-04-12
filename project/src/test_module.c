#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "custom_types.h"
#include "functions_for_cases.h"
#include "test_module.h"
#include "utils.h"

int check_test_rec_or_cr_limit_change(char* filename) {
    FILE* test_ptr = fopen(filename, "w+");
    if (!test_ptr) {
        printf("Not access to file\n");
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    if (test_rec_or_cr_limit_change_file(test_ptr)) {
        printf("Test was failed\n");
        fclose(test_ptr);
        return ERROR_TEST_FAILED;
    }

    return 0;
}
int check_test_trans(char* filename) {
    FILE* test_ptr = fopen(filename, "w+");
    if (!test_ptr) {
        printf("Not access to file\n");
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    if (test_trans_file(test_ptr)) {
        printf("Test was failed\n");
        fclose(test_ptr);
        return ERROR_TEST_FAILED;
    }
    return 0;
}

int test_rec_or_cr_limit_change_file(FILE* test_ptr) {
    if (!test_ptr) {
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    data_t expected_data = {
        .number = 1,
        .name = "123",
        .surname = "123",
        .address = "123",
        .tel_number = "123",
        .indebtedness = 1.2,
        .credit_limit = 1.3,
        .cash_payments = 1.4
    };

    data_t got_data = {0};

    if (print_in_rec_file(test_ptr, expected_data)) {
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    rewind(test_ptr);

    int assigned_values = 0;
    while ((assigned_values = fscanf(test_ptr, "%d%19s%19s%29s%14s%lf%lf%lf",
                                                        &got_data.number,
                                                        got_data.name,
                                                        got_data.surname,
                                                        got_data.address,
                                                        got_data.tel_number,
                                                        &got_data.indebtedness,
                                                        &got_data.credit_limit,
                                                        &got_data.cash_payments)) != -1) {
        if (assigned_values == 8) {
            break;
        }
        return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
    }

    assert(expected_data.number == got_data.number);
    assert(fabs(expected_data.indebtedness-got_data.indebtedness) < EPS);
    assert(fabs(expected_data.credit_limit-got_data.credit_limit) < EPS);
    assert(fabs(expected_data.cash_payments-got_data.cash_payments) < EPS);
    assert(!strcmp(expected_data.name, got_data.name));
    assert(!strcmp(expected_data.surname, got_data.surname));
    assert(!strcmp(expected_data.address, got_data.address));
    assert(!strcmp(expected_data.tel_number, got_data.tel_number));

    return 0;
}

int test_trans_file(FILE* test_ptr) {
    if (!test_ptr) {
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    data_t expected_data = {
        .number = 1,
        .cash_payments = 1.4
    };

    data_t got_data = {0};

    if (print_in_trans_file(test_ptr, expected_data)) {
        return ERROR_WRONG_VALUE_OF_PTR;
    }

    rewind(test_ptr);

    int assigned_values = 0;
    while ((assigned_values = fscanf(test_ptr, "%d%lf",
                                                &got_data.number,
                                                &got_data.cash_payments)) != -1) {
        if (assigned_values == 2) {
            break;
        }
        return ERROR_WRONG_VALUE_OF_INPUT_RETURN;
    }

    assert(expected_data.number == got_data.number);
    assert(fabs(expected_data.cash_payments-got_data.cash_payments) < EPS);

    return 0;
}

int main(void) {
    if (check_test_rec_or_cr_limit_change(RECORD_FILE)) {
        return ERROR_TEST_FAILED;
    }

    if (check_test_trans(TRANSACTION_FILE)) {
        return ERROR_TEST_FAILED;
    }

    if (check_test_rec_or_cr_limit_change(CREDIT_LIMIT_FILE)) {
        return ERROR_TEST_FAILED;
    }

    printf("Print/scan test for record file was successful\n");
    printf("Print/scan test for transaction file was successful\n");
    printf("Print/scan test for credit limit change file was successful\n");
    return 0;
}
