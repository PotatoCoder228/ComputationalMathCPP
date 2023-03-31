//
// Created by sasha on 29.03.2023.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Equation.h"

namespace common_utils {
    double func1(double x) {
        return (2.74 * x * x * x) - (1.93 * x * x) - (15.28 * x) - 3.72;
    }

    double func1_der(double x) {
        return (8.22 * x * x) - (3.86 * x) - 15.28;
    }

    double func1_der2(double x) {
        return (15.44 * x) - 3.86;
    }

    double func2(double x) {
        return (-1.38 * x * x * x) - (5.42 * x * x) + (2.57 * x) + 10.95;
    }

    double func2_der(double x) {
        return (-4.14 * x * x) - (10.84 * x) + 2.57;
    }

    double func2_der2(double x) {
        return (-8.28 * x) - 10.84;
    }

    double func3(double x) {
        return (x * x * x) + (2.84 * x * x) - (5.606 * x) - 14.766;
    }

    double func3_der(double x) {
        return (3 * x * x) + (5.68 * x) - 5.606;
    }

    double func3_der2(double x) {
        return (6 * x) + 5.68;
    }

    Equation::Equation(solv_func solv, func fun, func der, func der2) {
        this->derivative = der;
        this->function = fun;
        this->solver = solv;
        this->derivative2 = der2;
    }

    Equation::~Equation() = default;

    void Equation::set_interval(double begin, double end) {
        this->start = begin;
        this->finish = end;
    }

    void Equation::set_eps(double e) {
        this->eps = e;
    }

    bool Equation::root_validation(Equation &eq) {
        double buf = eq.function(eq.start) * eq.function(eq.finish);
        if (buf >= 0) {
            std::cout << "Корней на отрезке не существует." << std::endl;
            return false;
        }
        buf = eq.derivative(eq.start) * eq.derivative(eq.finish);
        if (buf >= 0) {
            return true;
        }
        std::cout << "Невалидный интервал. \\_0_0_/" << std::endl;
        return false;
    }

    double Equation::solve() {
        return this->solver(*this);
    }

    typedef double (*func)(double x);

    static void draw(double point, func function, double start, double finish) {
        FILE *gp = popen("gnuplot -persistent", "w");
        fprintf(gp, "set grid\n");
        fprintf(gp, "set xrange [%lf:%lf]\n", start - 10, finish + 10);
        fprintf(gp, "set xlabel \"X axis\"\n");
        fprintf(gp, "set ylabel \"Y axis\"\n");
        fprintf(gp, "set style line 2 lc rgb 'black' pt 7\n");
        fprintf(gp, "plot ");
        if (function == func1) {
            fprintf(gp, " %s, ", eq_1_str.c_str());
        } else if (function == func2) {
            fprintf(gp, " %s, ", eq_2_str.c_str());
        } else {
            fprintf(gp, " %s, ", eq_3_str.c_str());
        }
        fprintf(gp, "'-' w p ls 2\n");
        fprintf(gp, "%lf %lf\ne\n", point, function(point));
        fflush(gp);
    }

    double Equation::half_del_method(Equation &eq) {
        double int_begin = eq.start;
        double int_finish = eq.finish;
        double x;
        double iter_counter = 0;
        double buf;
        do {
            iter_counter++;
            x = (eq.start + eq.finish) / 2;
            buf = std::fabs(eq.function(x));
            if (std::fabs(eq.start - eq.finish) < eq.eps) break;
            if (buf * eq.function(eq.finish) < 0) {
                eq.start = x;
            } else {
                eq.finish = x;
            }
        } while (buf > eq.eps);
        draw(x, eq.function, int_begin, int_finish);
        std::cout << "Количество итераций: " << iter_counter << std::endl;
        std::cout << "Искомый корень: " << x << std::endl;
        return x;
    }

    double Equation::newton_method(Equation &eq) {
        double int_begin = eq.start;
        double int_finish = eq.finish;
        double x = eq.finish;
        if (eq.function(eq.start) * eq.derivative2(eq.start) > 0) {
            x = eq.start;
        }
        int iter_counter = 0;
        double func;
        double func_der;
        double prev_x;
        do {
            iter_counter++;
            func = eq.function(x);
            func_der = eq.derivative(x);
            prev_x = x;
            x = prev_x - (func / func_der);
        } while (std::fabs(func / func_der) > eq.eps && std::fabs(func) > eq.eps && std::fabs(x - prev_x) > eq.eps);
        draw(x, eq.function, int_begin, int_finish);
        std::cout << "Количество итераций: " << iter_counter << std::endl;
        std::cout << "Искомый корень: " << x << std::endl;
        return x;
    }

    bool Equation::check_simple_iter_convergence(double lambda) {
        double buf_1 = std::fabs(1 + (this->derivative(this->start) * lambda));
        double buf_2 = std::fabs(1 + (this->derivative(this->finish) * lambda));
        if (buf_1 >= 1 || buf_2 >= 1) {
            return false;
        }
        return true;
    }

    double Equation::simple_iter_method(Equation &eq) {
        double int_begin = eq.start;
        double int_finish = eq.finish;
        double x = eq.start;
        double abs_f_start = std::fabs(eq.derivative(eq.start));
        double abs_f_finish = std::fabs(eq.derivative(eq.finish));
        double max = abs_f_start > abs_f_finish ? abs_f_start : abs_f_finish;
        double lambda = -(1 / (max));
        bool checker = eq.check_simple_iter_convergence(lambda);
        if (!checker) {
            std::cout << "Метод расходится на этом интервале..." << std::endl;
            return 0;
        }
        int iter_counter = 0;
        double prev_x;
        do {
            iter_counter++;
            prev_x = x;
            x = x + lambda * eq.function(x);
        } while (std::fabs(prev_x - x) > eq.eps);
        draw(x, eq.function, int_begin, int_finish);
        std::cout << "Количество итераций: " << iter_counter << std::endl;
        std::cout << "Искомый корень: " << x << std::endl;
        return x;
    }
} // common_utils