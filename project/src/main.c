#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions_for_cases.h"
#include "prints.h"

#define WRITE_CLIENT_DATA            1
#define WRITE_TRANSACTION_DATA       2
#define UPDATE_BASE                  3

#define ERROR_WRONG_INP             (-1)
#define ERROR_WRONG_PTR_VALUE       (-2)
#define ERROR_WRONG_FLAG            (-3)


int main(void) {
    int choice = 0;

    data_t client_data = {0};

    data_t transfer = {0};

    input_prompt();

    int read_values = 0;
    while ((read_values = scanf("%d", &choice)) != -1) {
        if (read_values != 1) {
            return ERROR_WRONG_INP;
        }
        switch (choice) {
            case WRITE_CLIENT_DATA:
                if (writing_client_data(client_data) == ERROR_WRONG_PTR) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }
                if (writing_client_data(client_data) == ERROR_WRONG_INPUT) {
                    return ERROR_WRONG_INP;
                }
                if (writing_client_data(client_data) == ERROR_NULL_PTR) {
                    return ERROR_WRONG_PTR_VALUE;
                }

                break;
            case WRITE_TRANSACTION_DATA:
                if (writing_transfer_data(transfer) == ERROR_WRONG_PTR) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }
                if (writing_transfer_data(transfer) == ERROR_WRONG_INPUT) {
                    return ERROR_WRONG_INP;
                }
                if (writing_transfer_data(transfer) == ERROR_NULL_PTR) {
                    return ERROR_WRONG_PTR_VALUE;
                }

                break;
            case UPDATE_BASE:
                if (writing_changes(client_data, transfer) == ERROR_WRONG_PTR) {
                    puts("No access\n");
                    return ERROR_WRONG_PTR_VALUE;
                }
                if (writing_changes(client_data, transfer) == ERROR_WRONG_INPUT) {
                    return ERROR_WRONG_INP;
                }
                if (writing_changes(client_data, transfer) == ERROR_NULL_PTR) {
                    return ERROR_WRONG_PTR_VALUE;
                }

                break;
            default:
                puts("Error, wrong choice\n");
                return ERROR_WRONG_FLAG;
        }
        input_prompt();
    }
    return 0;
}
