#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

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

    while (fscanf(fileptr, "%zu%zu", &matrix->rows, &matrix->columns) != -1) {}

    matrix->ptr = malloc(sizeof(size_t*)*matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        if (!(matrix->ptr[i] = malloc(sizeof(size_t)*matrix->columns))) {
            free(matrix->ptr);
            free(matrix);
            fclose(fileptr);
            return NULL;
        }
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix -> columns; j++) {
            fscanf(fileptr, "%zu", &matrix->ptr[i][j]);
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

    matrix->ptr = malloc(sizeof(size_t*)*rows);

    if (!matrix->ptr) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if (!(matrix->ptr[i] = malloc(sizeof(size_t)*cols))) {
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
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix || !rows) {
        return -1;
    }

    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix || !cols) {
        return -1;
    }
    *cols = matrix->columns;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix || !val) {
        return -1;
    }

    *val = matrix->ptr[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return -1;
    }

    matrix->ptr[row][col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix -> columns; j++) {
            matrix->ptr[i][j] *= val;
        }
    }
    return (Matrix*) matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix *transposition = malloc(sizeof(Matrix));

    if (!transposition) {
        return NULL;
    }

    transposition->rows = matrix->columns;
    transposition->columns = matrix->rows;

    transposition->ptr = malloc(sizeof(size_t*)*transposition->rows);

    if (!transposition->ptr) {
        free(transposition);
        return NULL;
    }

    for (size_t i = 0; i < transposition->rows; i++) {
        if (!(transposition->ptr[i] = malloc(sizeof(size_t)*transposition->columns))) {
            free(transposition->ptr);
            free(transposition);
            return NULL;
        }
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            transposition->ptr[j][i] = matrix->ptr[i][j];
        }
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->ptr[i]);
    }
    free(matrix->ptr);

    return transposition;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->rows != r->rows && l->columns != r->columns) {
        return NULL;
    }
    Matrix *sum_matrix = malloc(sizeof(Matrix));

    if (!sum_matrix) {
        return NULL;
    }

    sum_matrix->rows = l->rows;
    sum_matrix->columns = l->columns;

    sum_matrix->ptr = malloc(sizeof(size_t*)*sum_matrix->rows);

    if (!sum_matrix->ptr) {
        free(sum_matrix);
        return NULL;
    }

    for (size_t i = 0; i < sum_matrix->rows; i++) {
        if (!(sum_matrix->ptr[i] = malloc(sizeof(size_t)*sum_matrix->columns))) {
            free(sum_matrix->ptr);
            free(sum_matrix);
            return NULL;
        }
    }

    for (size_t i = 0; i <sum_matrix->rows; i++) {
        for (size_t j = 0; j < sum_matrix->columns; j++) {
            sum_matrix->ptr[i][j] = l->ptr[i][j] + r->ptr[i][j];
        }
    }

    return sum_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->rows != r->rows && l->columns != r->columns) {
        return NULL;
    }

    Matrix *sub_matrix = malloc(sizeof(Matrix));

    if (!sub_matrix) {
        return NULL;
    }

    sub_matrix->rows = l->rows;
    sub_matrix->columns = l->columns;

    sub_matrix->ptr = malloc(sizeof(size_t*)*sub_matrix->rows);

    if (!sub_matrix->ptr) {
        free(sub_matrix);
        return NULL;
    }

    for (size_t i = 0; i < sub_matrix->rows; i++) {
        if (!(sub_matrix->ptr[i] = malloc(sizeof(size_t)*sub_matrix->columns))) {
            free(sub_matrix->ptr);
            free(sub_matrix);
            return NULL;
        }
    }

    for (size_t i = 0; i <sub_matrix->rows; i++) {
        for (size_t j = 0; j < sub_matrix->columns; j++) {
            sub_matrix->ptr[i][j] = l->ptr[i][j] - r->ptr[i][j];
        }
    }
    return sub_matrix;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }

    if (l->columns != r->rows) {
        return NULL;
    }

    Matrix *mul_matrix = malloc(sizeof(Matrix));

    if (!mul_matrix) {
        return NULL;
    }

    mul_matrix->rows = l->rows;
    mul_matrix->columns = r->columns;

    mul_matrix->ptr = malloc(sizeof(size_t*)*mul_matrix->rows);

    if (!mul_matrix->ptr) {
        free(mul_matrix);
        return NULL;
    }

    for (size_t i = 0; i < mul_matrix->rows; i++) {
        if (!(mul_matrix->ptr[i] = malloc(sizeof(size_t)*mul_matrix->columns))) {
            free(mul_matrix->ptr);
            free(mul_matrix);
            return NULL;
        }
    }

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
        return -1;
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
