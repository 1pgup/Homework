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

    for (size_t i = 0; i <sum_matrix->rows; i++) {
        for (size_t j = 0; j < sum_matrix->columns; j++) {
            sum_matrix->ptr[i][j] = l->ptr[i][j] + r->ptr[i][j];
        }
    }

    return sum_matrix;
}

static Matrix* sec_sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    Matrix *sub_matrix = create_matrix(l->rows, l->columns);

    for (size_t i = 0; i <sub_matrix->rows; i++) {
        for (size_t j = 0; j < sub_matrix->columns; j++) {
            sub_matrix->ptr[i][j] = l->ptr[i][j] - r->ptr[i][j];
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
    if (path_file == NULL) {
        return NULL;
    }

    FILE *fileptr = fopen(path_file, "r");

    if (fileptr == NULL) {
        return NULL;
    }

    Matrix *matrix = malloc(sizeof(Matrix));

    if (!matrix) {
        fclose(fileptr);
        return NULL;
    }

    fscanf(fileptr, "%zu%zu", &matrix->rows, &matrix->columns);

    matrix->ptr = malloc(sizeof(double*)*matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        if (!(matrix->ptr[i] = malloc(sizeof(double)*matrix->columns))) {
            free(matrix->ptr);
            free(matrix);
            fclose(fileptr);
            return NULL;
        }
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix -> columns; j++) {
            fscanf(fileptr, "%lf", &matrix->ptr[i][j]);
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

    matrix->ptr = malloc(sizeof(double*)*matrix->rows);

    if (!matrix->ptr) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        if (!(matrix->ptr[i] = malloc(sizeof(double)*matrix->columns))) {
            free(matrix->ptr);
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
        free(matrix->ptr[i]);
    }
    free(matrix->ptr);
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

    *val = matrix->ptr[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return ERROR_NULL_PTR;
    }

    matrix->ptr[row][col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }

    Matrix *mul_scalar = create_matrix(matrix->rows, matrix->columns);

    for (size_t i = 0; i < mul_scalar->rows; i++) {
        for (size_t j = 0; j < mul_scalar -> columns; j++) {
            mul_scalar->ptr[i][j] = matrix->ptr[i][j] * val;
        }
    }

    return mul_scalar;
}

Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix *transposition = create_matrix(matrix->columns, matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            transposition->ptr[j][i] = matrix->ptr[i][j];
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

    for (size_t i = 0; i < mul_matrix->rows; i++) {
        for (size_t j = 0; j < mul_matrix->columns; j++) {
            mul_matrix->ptr[i][j] = 0;
            for (size_t k = 0; k < l->columns; k++) {
                mul_matrix->ptr[i][j] += l->ptr[i][k] * r->ptr[k][j];
            }
        }
    }
    return mul_matrix;
}

// Extra operations
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
