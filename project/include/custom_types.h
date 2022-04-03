#ifndef PROJECT_INCLUDE_CUSTOM_TYPES_H_
#define PROJECT_INCLUDE_CUSTOM_TYPES_H_

#define FORMAT_STRING_MAX_SIZE   10

enum sizes {
    NAMESIZE = 20,
    SURNAMESIZE = 20,
    ADDRESSSIZE = 30,
    TELNUMBERSIZE = 15
};

typedef struct master_record {
    int number;

    char name[NAMESIZE];
    char surname[SURNAMESIZE];
    char address[ADDRESSSIZE];
    char tel_number[TELNUMBERSIZE];

    double indebtedness;
    double credit_limit;
    double cash_payments;
} data_t;

#endif  //  PROJECT_INCLUDE_CUSTOM_TYPES_H_
