//
// Created by sasha on 29.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_EQUATION_H
#define COMPUTATIONALMATHCPP_EQUATION_H

namespace common_utils {
    static std::string eq_1_str("2.74*(x**3)-1.93*(x**2)-15.28*x-3.72");
    static std::string eq_2_str("(-1.38)*(x**3)-5.42*(x**2)+2.57*x+10.95");
    static std::string eq_3_str("x**3+2.84*(x**2)-5.606*x-14.766");
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
