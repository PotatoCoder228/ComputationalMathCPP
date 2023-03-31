//
// Created by sasha on 31.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_MATRIX_H
#define COMPUTATIONALMATHCPP_MATRIX_H

#include <cstdlib>

typedef struct matrix matrix;

void matrix_init(matrix *matrix, double **array, size_t rows, size_t columns);

matrix *new_matrix();

double **matrix_get_matrix(matrix *matrix);

size_t matrix_get_rows(matrix *matrix);

size_t matrix_get_columns(matrix *matrix);

int64_t matrix_swap_rows(matrix *matrix, size_t first_row, size_t second_row);

void matrix_print(matrix *matrix);

#endif //COMPUTATIONALMATHCPP_MATRIX_H
