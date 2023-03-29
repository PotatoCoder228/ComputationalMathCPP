//
// Created by sasha on 29.03.2023.
//

#include "Equation.h"

namespace common_utils {
    double func1(double x){
        return 2.74*x*x*x-1.93*x*x-15.28*x-3.72;
    }
    double func1_der(double x){
        return 8.22*x*x-3.86*x-15.28;
    }
    double func2(double x){
        return -1.38*x*x*x-5.42*x*x+2.57*x+10.95;
    }
    double func2_der(double x){
        return -4.14*x*x-10.84*x+2.57;
    }
    double func3(double x){
        return x*x*x+2.84*x*x-5.606*x-14.766;
    }
    double func3_der(double x){
        return 3*x*x+5.68*x-5.606;
    }
    Equation::Equation(solv_func solv, func fun, func der) {
        this->derivative = der;
        this->function = fun;
        this->solver = solv;
    }

    Equation::~Equation() = default;

    void Equation::set_interval(double begin, double end){
        this->start = begin;
        this->finish = end;
    }

    void Equation::set_eps(double e){
        this->eps = e;
    }

    double Equation::solve(){
        return this->solver();
    }

    double Equation::half_del_method(){

    }
    double Equation::newton_method(){

    }
    double Equation::simple_iter_method(){

    }
} // common_utils