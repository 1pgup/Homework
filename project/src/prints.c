#include <stdio.h>

#include "prints.h"

void print_action() {
    printf("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n\n");
}
void print_client_inf() {
    printf("1 Number account:\n2 Client name:\n3 Surname:\n4 Addres client:\n");
    printf("5 Client Telnum:\n6 Client indebtedness:\n7 Client credit limit:\n8 Client cash payments:\n\n");
}
void print_transfer_inf() {
    printf("1 Number account:\n2 Client cash payments:\n\n");
}
