//
// Created by sasha on 31.03.2023.
//

#include <cmath>
#include <vector>
#include <iostream>
#include "EquationsSystem.h"
#include "lin_eq_solver.h"

namespace common_utils {
    static void draw_system(EquationsSystem &system) {
        FILE *gp = popen("gnuplot -persistent", "w");
        fprintf(gp, "set grid\n");
        fprintf(gp, "set view 0,0\n");
        fprintf(gp, "set cont base\n");
        fprintf(gp, "unset surface\n");
        fprintf(gp, "set size square\n");
        fprintf(gp, "set cntrparam levels discrete 0,0\n");
        if (system.first == sys_func_11) {
            fprintf(gp, "f1(x,y)=%s\n", sys_1_1_str.c_str());
            fprintf(gp, "f2(x,y)=%s\n", sys_1_2_str.c_str());
            fprintf(gp, "splot f1(x,y), f2(x,y)\n");
        } else {
            fprintf(gp, "f1(x,y)=%s\n", sys_2_1_str.c_str());
            fprintf(gp, "f2(x,y)=%s\n", sys_2_2_str.c_str());
            fprintf(gp, "splot f1(x,y), f2(x,y)\n");
        }
        /*
        if (function == func1) {
            fprintf(gp, " %s, ", eq_1_str.c_str());
        } else if (function == func2) {
            fprintf(gp, " %s, ", eq_2_str.c_str());
        } else {
            fprintf(gp, " %s, ", eq_3_str.c_str());
        }
        fprintf(gp, "'-' w p ls 2\n");
        fprintf(gp, "%lf %lf\ne\n", point, function(point));
        */
        fflush(gp);
    }

    void EquationsSystem::solve() {
        double prev_x;
        double prev_y;
        double **m_array = matrix_get_matrix(this->matrix);
        std::vector<double> x_vector;
        std::vector<double> y_vector;
        double *results = static_cast<double *>(malloc(sizeof(double) * 2));
        do {
            m_array[0][0] = x_11(this->x0, this->y0);
            m_array[0][1] = y_11(this->x0, this->y0);
            m_array[0][2] = -first(this->x0, this->y0);
            m_array[1][0] = x_21(this->x0, this->y0);
            m_array[1][1] = y_21(this->x0, this->y0);
            m_array[1][2] = -second(this->x0, this->y0);
            int64_t k = matrix_to_triangular_view(matrix);
            double det = matrix_det_from_triangular_view(matrix, k);
            if (det == 0) {
                std::cout << "Детерминант равен 0, решить невозможно." << std::endl;
                return;
            }
            gauss_method_inverse(matrix, results);
            prev_x = this->x0;
            prev_y = this->y0;
            this->x0 = this->x0 + results[0];
            this->y0 = this->y0 + results[1];
            x_vector.push_back(std::fabs(results[0]));
            y_vector.push_back(std::fabs(results[1]));
        } while (std::fabs(results[0]) > this->eps &&
                 std::fabs(results[1]) > this->eps);
        std::cout << "Вектор погрешностей:" << std::endl;
        for (int i = x_vector.size(); !x_vector.empty(); i--) {
            std::cout << "x_" << i << ": " << x_vector.back() << std::endl;
            x_vector.pop_back();
            std::cout << "y_" << i << ": " << y_vector.back() << std::endl;
            y_vector.pop_back();
        }
        std::cout << "Решение:" << std::endl;
        std::cout << "x: " << this->x0 << std::endl;
        std::cout << "y: " << this->y0 << std::endl;
        draw_system(*this);
        free(m_array[0]);
        free(m_array[1]);
        free(m_array);
        free(results);
    }
} // common_utils