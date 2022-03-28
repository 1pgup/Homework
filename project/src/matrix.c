#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file) {
    Matrix *matrix = malloc(sizeof(Matrix));

    FILE *fileptr = fopen(path_file, "r");
    fscanf(fileptr, "%zu%zu", &matrix->rows, &matrix->collumns);

    matrix->ptr = malloc(sizeof(size_t*)*matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        matrix->ptr[i] = malloc(sizeof(size_t)*matrix->collumns);
    }

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix -> collumns; j++) {
            fscanf(fileptr, "%zu", &matrix->ptr[i][j]);
        }
    }

    fclose(fileptr);
    return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->ptr = malloc(sizeof(size_t*)*rows);

    for (size_t i = 0; i < rows; i++) {
        matrix->ptr[i] = malloc(sizeof(size_t)*cols);
    }

    return matrix;
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->ptr[i]);
    }
    free(matrix->ptr);
}


