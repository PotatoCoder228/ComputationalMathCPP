//
// Created by sasha on 29.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_EQUATION_H
#define COMPUTATIONALMATHCPP_EQUATION_H

namespace common_utils {
    double func1(double x);

    double func1_der(double x);

    double func1_der2(double x);

    double func2(double x);

    double func2_der(double x);

    double func2_der2(double x);

    double func3(double x);

    double func3_der(double x);

    double func3_der2(double x);

    class Equation {
        typedef double (*func)(double x);

        typedef double (*solv_func)(Equation &);

    private:
        solv_func solver;
        func function;
        func derivative;
        func derivative2;
        double start;
        double finish;
        double eps;
    public:
        Equation(solv_func solv, func fun, func der, func der2);

        static double half_del_method(Equation &);

        static double newton_method(Equation &);

        static double simple_iter_method(Equation &);

        void set_interval(double begin, double end);

        void set_eps(double e);

        double solve();

        bool root_validation(Equation &);

        ~Equation();
    };

} // common_utils

#endif //COMPUTATIONALMATHCPP_EQUATION_H
