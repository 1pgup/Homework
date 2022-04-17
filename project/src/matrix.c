#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

static Matrix* (*foo)(const Matrix*, const Matrix*);

// Secondary functions
static Matrix* sec_sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    Matrix *sum_matrix = create_matrix(l->rows, l->columns);
    if (!sum_matrix) {
        return NULL;
    }

    for (size_t i = 0; i <sum_matrix->rows; i++) {
        for (size_t j = 0; j < sum_matrix->columns; j++) {
            sum_matrix->element[i][j] = l->element[i][j] + r->element[i][j];
        }
    }

    return sum_matrix;
}

static Matrix* sec_sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    Matrix *sub_matrix = create_matrix(l->rows, l->columns);
    if (!sub_matrix) {
        return NULL;
    }

    for (size_t i = 0; i <sub_matrix->rows; i++) {
        for (size_t j = 0; j < sub_matrix->columns; j++) {
            sub_matrix->element[i][j] = l->element[i][j] - r->element[i][j];
        }
    }

    return sub_matrix;
}

static Matrix* matrix_sum_or_sub(Matrix* (*foo)(const Matrix*, const Matrix*),
                                const Matrix* l,
                                const Matrix* r) {
    if (!l || !r || !foo) {
        return NULL;
    }

    return foo(l , r);
}
// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    if (!path_file) {
        return NULL;
    }

    FILE *fileptr = fopen(path_file, "r");

    if (!fileptr) {
        return NULL;
    }

    Matrix *matrix = malloc(sizeof(Matrix));

    if (!matrix) {
        fclose(fileptr);
        return NULL;
    }

    int amount_of_asigned_values = 0;
    int rows = 0;
    int cols = 0;
    while ((amount_of_asigned_values = fscanf(fileptr, "%d%d", &rows, &cols)) != -1) {
        if (amount_of_asigned_values == 2) {
            break;
        }
        fclose(fileptr);
        free(matrix);
        return NULL;
    }

    if ((rows < 0) || (cols < 0)) {
        fclose(fileptr);
        free(matrix);
        return NULL;
    }

    matrix->rows = rows;
    matrix->columns = cols;

    matrix->element = malloc(sizeof(double*)*matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        if (!(matrix->element[i] = malloc(sizeof(double)*matrix->columns))) {
            free(matrix->element);
            free(matrix);
            fclose(fileptr);
            return NULL;
        }
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix -> columns; j++) {
            fscanf(fileptr, "%lf", &matrix->element[i][j]);
        }
    }

    fclose(fileptr);
    return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = malloc(sizeof(Matrix));

    if (!matrix) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->columns = cols;

    matrix->element = malloc(sizeof(double*)*matrix->rows);

    if (!matrix->element) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        if (!(matrix->element[i] = malloc(sizeof(double)*matrix->columns))) {
            free(matrix->element);
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void free_matrix(Matrix* matrix) {
    if (!matrix) {
        return;
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->element[i]);
    }
    free(matrix->element);
    free(matrix);
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix || !rows) {
        return ERROR_NULL_PTR;
    }

    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix || !cols) {
        return ERROR_NULL_PTR;
    }
    *cols = matrix->columns;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix || !val) {
        return ERROR_NULL_PTR;
    }

    if ((row > matrix->rows) || (col > matrix->columns)) {
        return ERROR_TOO_MUCH_VALUE_OF_ROW_OR_COL;
    }

    *val = matrix->element[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return ERROR_NULL_PTR;
    }
    if ((row > matrix->rows) || (col > matrix->columns)) {
        return ERROR_TOO_MUCH_VALUE_OF_ROW_OR_COL;
    }

    matrix->element[row][col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }

    Matrix *mul_scalar = create_matrix(matrix->rows, matrix->columns);
    if (!mul_scalar) {
        return NULL;
    }

    for (size_t i = 0; i < mul_scalar->rows; i++) {
        for (size_t j = 0; j < mul_scalar -> columns; j++) {
            mul_scalar->element[i][j] = matrix->element[i][j] * val;
        }
    }

    return mul_scalar;
}

Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }

    Matrix *transposition = create_matrix(matrix->columns, matrix->rows);
    if (!transposition) {
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            transposition->element[j][i] = matrix->element[i][j];
        }
    }

    return transposition;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->rows != r->rows || l->columns != r->columns) {
        return NULL;
    }

    foo = &sec_sum;

    return matrix_sum_or_sub(*foo, l, r);
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->rows != r->rows || l->columns != r->columns) {
        return NULL;
    }

    foo = &sec_sub;

    return matrix_sum_or_sub(*foo, l, r);
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->columns != r->rows) {
        return NULL;
    }

    Matrix *mul_matrix = create_matrix(l->rows, r->columns);
    if (!mul_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < mul_matrix->rows; i++) {
        for (size_t j = 0; j < mul_matrix->columns; j++) {
            mul_matrix->element[i][j] = 0;
            for (size_t k = 0; k < l->columns; k++) {
                mul_matrix->element[i][j] += l->element[i][k] * r->element[k][j];
            }
        }
    }
    return mul_matrix;
}

// Extra operations (not done)
int det(const Matrix* matrix, double* val) {
    if (!matrix || !val) {
        return ERROR_NULL_PTR;
    }
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    return NULL;
}

Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    return NULL;
}
