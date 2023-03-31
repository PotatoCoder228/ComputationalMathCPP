//
// Created by sasha on 31.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_EQUATIONSSYSTEM_H
#define COMPUTATIONALMATHCPP_EQUATIONSSYSTEM_H

#include <string>
#include "matrix.h"

namespace common_utils {

    static std::string sys_1_1_str = "x**2+y**2=4";
    static std::string sys_1_2_str = "-3x**2+y=0";
    static std::string sys_2_1_str = "x*x*x+x*x+y=6";
    static std::string sys_2_2_str = "x*x-12*y=7";

    double sys_func_11(double x, double y){
        return (x*x)+(y*y)-4;
    }
    double sys_func_12(double x, double y){
        return (-3*x*x)+y;
    }

    double sys_func_21(double x, double y){
        return (x*x*x) + (x*x) - 6 + y;
    }

    double sys_func_22(double x, double y){
        return (x*x) -(12*y) + 7;
    }

    double sys_11_dx(double x, double y){
        return 2*x;
    }

    double sys_11_dy(double x, double y){
        return 2*y;
    }

    double sys_12_dx(double x, double y){
        return -6*x;
    }

    double sys_12_dy(double x, double y){
        return 1;
    }

    class EquationsSystem {
        typedef double (*func)(double,double);
    public:
        std::string x_polar;
        std::string y_polar;
        double x0;
        double y0;
        double eps;
        matrix *matrix;
        func x_11;
        func y_11;
        func x_21;
        func y_21;
        func first;
        func second;
        double dx;
        double dy;

        void set_first_eq() {
            matrix = new_matrix();
            double **m_array = static_cast<double **>(malloc(sizeof(double *)));
            m_array[0] = static_cast<double *>(malloc(sizeof(double)));
            m_array[1] = static_cast<double *>(malloc(sizeof(double)));
            matrix_init(matrix, m_array, 2, 2);//TODO
        }
        void solve();
    };

} // common_utils

#endif //COMPUTATIONALMATHCPP_EQUATIONSSYSTEM_H
