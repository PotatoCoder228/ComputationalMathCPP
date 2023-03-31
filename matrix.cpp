//
// Created by sasha on 31.03.2023.
//

#include <cstdio>
#include "matrix.h"

typedef struct matrix {
    double **matrix;
    size_t rows;
    size_t columns;
} matrix;

matrix *new_matrix() {
    return (matrix *) malloc(sizeof(matrix));
}

void matrix_init(matrix *matrix, double **array, size_t rows, size_t columns) {
    matrix->matrix = array;
    matrix->rows = rows;
    matrix->columns = columns;
}

double **matrix_get_matrix(matrix *matrix) {
    return matrix->matrix;
}

size_t matrix_get_rows(matrix *matrix) {
    return matrix->rows;
}

size_t matrix_get_columns(matrix *matrix) {
    return matrix->columns;
}

int64_t matrix_swap_rows(matrix *matrix, size_t first_row, size_t second_row) {
    if (matrix != nullptr && second_row < matrix_get_rows(matrix) && matrix_get_rows(matrix) > first_row) {
        double **ptrs_array = matrix->matrix;
        double *buf = ptrs_array[first_row];
        ptrs_array[first_row] = ptrs_array[second_row];
        ptrs_array[second_row] = buf;
        return 1;
    }
    return 0;
}


void matrix_print(matrix *matrix) {
    double **m_array = matrix->matrix;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            printf("%lf ", m_array[i][j]);
        }
        printf("%s", "\n");
    }
}

void matrix_destroy(matrix *matrix) {
    free(matrix);
}