#ifndef PROJECT_INCLUDE_CUSTOM_TYPES_H_
#define PROJECT_INCLUDE_CUSTOM_TYPES_H_

#define FORMAT_STRING_MAX_SIZE   10

enum sizes {
    NameSize = 20,
    SurnameSize = 20,
    AddressSize = 30,
    TelNumberSize = 15
};

struct masterRecord {
    int number;

    char name[NameSize];
    char surname[SurnameSize];
    char address[AddressSize];
    char tel_number[TelNumberSize];

    double indebtedness;
    double credit_limit;
    double cash_payments;
};
typedef struct masterRecord Data_t;

#endif  //  PROJECT_INCLUDE_CUSTOM_TYPES_H_
