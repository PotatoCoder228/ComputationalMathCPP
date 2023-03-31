//
// Created by sasha on 31.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_LIN_EQ_SOLVER_H
#define COMPUTATIONALMATHCPP_LIN_EQ_SOLVER_H

#include "matrix.h"

enum equation_error {
    DET_IS_EQ_ZERO = 1000
};

int64_t matrix_to_triangular_view(matrix *matrix);

double matrix_det_from_triangular_view(matrix *matrix, int64_t rows_swaps);

void gauss_method_inverse(matrix *matrix, double *results);

void matrix_destroy(matrix *matrix);

void print_SLAE(matrix *matrix);

void print_double(double k);

#endif //COMPUTATIONALMATHCPP_LIN_EQ_SOLVER_H
