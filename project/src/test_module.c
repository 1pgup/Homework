#include "test_module.h"

int test_read_from_rec_file(FILE *file_ptr, Data_t inputed_data) {
    Data_t got_data;

    got_data.number = 0;
    got_data.indebtedness = 0;
    got_data.credit_limit = 0;
    got_data.cash_payments = 0;
    for (int i = 0; i < NameSize; i++) {
        got_data.name[i] = 0;
    }
    for (int i = 0; i < SurnameSize; i++) {
        got_data.surname[i] = 0;
    }
    for (int i = 0; i < AddressSize; i++) {
        got_data.address[i] = 0;
    }
    for (int i = 0; i < TelNumberSize; i++) {
        got_data.tel_number[i] = 0;
    }

    read_from_rec_file(file_ptr, got_data);

    if ((inputed_data.number == got_data.number)
      && (inputed_data.indebtedness == got_data.indebtedness)
      && (inputed_data.credit_limit == got_data.credit_limit)
      && (inputed_data.cash_payments == got_data.cash_payments)
      && (!strcmp(inputed_data.name, got_data.name))
      && (!strcmp(inputed_data.surname, got_data.surname))
      && (!strcmp(inputed_data.address, got_data.address))
      && (!strcmp(inputed_data.tel_number, got_data.tel_number))) {
        return 1;
    }
    return 0;
}

int test_read_from_trans_file(FILE *file_ptr, Data_t inputed_data) {
    Data_t got_data;

    got_data.number = 0;
    got_data.indebtedness = 0;
    got_data.credit_limit = 0;
    got_data.cash_payments = 0;
    for (int i = 0; i < NameSize; i++) {
        got_data.name[i] = 0;
    }
    for (int i = 0; i < SurnameSize; i++) {
        got_data.surname[i] = 0;
    }
    for (int i = 0; i < AddressSize; i++) {
        got_data.address[i] = 0;
    }
    for (int i = 0; i < TelNumberSize; i++) {
        got_data.tel_number[i] = 0;
    }

    read_from_trans_file(file_ptr, got_data);

    if ((inputed_data.number == got_data.number) && (inputed_data.cash_payments == got_data.cash_payments)) {
        return 1;
    }
    return 0;
}

void read_from_rec_file(FILE *file_ptr, Data_t got_data) {
    fscanf(file_ptr, "%d%19s%19s%29s%14s%lf%lf%lf",
                &got_data.number,
                got_data.name,
                got_data.surname,
                got_data.address,
                got_data.tel_number,
                &got_data.indebtedness,
                &got_data.credit_limit,
                &got_data.cash_payments);
}

void read_from_trans_file(FILE *file_ptr, Data_t got_data) {
    fscanf(file_ptr, "%d%lf", &got_data.number, &got_data.cash_payments);
}
