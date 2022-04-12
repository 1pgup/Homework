#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions_for_cases.h"
#include "prints.h"

#define WRITE_CLIENT_DATA            1
#define WRITE_TRANSACTION_DATA       2
#define UPDATE_BASE                  3

int main(void) {
    int choice = 0;

    data_t client_data = {0};

    data_t transfer = {0};

    print_action();

    int read_values = 0;
    while ((read_values = scanf("%d", &choice)) != -1) {
        if (read_values != 1) {
            puts("Something went wrong\n\n");
        }
        switch (choice) {
            case WRITE_CLIENT_DATA:
                if (writing_client_data(client_data)) {
                    puts("Something went wrong\n\n");
                }

                break;
            case WRITE_TRANSACTION_DATA:
                if (writing_transfer_data(transfer)) {
                    puts("Something went wrong\n\n");
                }

                break;
            case UPDATE_BASE:
                if (writing_changes(client_data, transfer)) {
                    puts("Something went wrong\n\n");
                }

                break;
            default:
                puts("Error, wrong choice, try one more time\n\n");
        }
        print_action();
    }
    return 0;
}
