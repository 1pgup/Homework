#ifndef PROJECT_INCLUDE_CUSTOM_TYPES_H_
#define PROJECT_INCLUDE_CUSTOM_TYPES_H_

#define ERROR_WRONG_VALUE_OF_INPUT_RETURN      (-1)
#define ERROR_NULL_PTR                         (-2)

enum sizes {
    NAME_SIZE = 20,
    SURNAME_SIZE = 20,
    ADDRESS_SIZE = 30,
    TELNUMBER_SIZE = 15
};

typedef struct master_record {
    int number;

    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char address[ADDRESS_SIZE];
    char tel_number[TELNUMBER_SIZE];

    double indebtedness;
    double credit_limit;
    double cash_payments;
} data_t;

#endif  //  PROJECT_INCLUDE_CUSTOM_TYPES_H_
