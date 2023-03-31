//
// Created by sasha on 29.03.2023.
//

#include "UserCommand.h"
#include "Equation.h"
#include "EquationsSystem.h"
#include <fstream>

namespace common_utils {
    void help_command(Console &console) {
        using std::cout;
        using std::endl;
        cout << "help - справка по командам;" << endl;
        cout << "nle - решение НУ;" << endl;
        cout << "snle - решение СНУ;" << endl;
        cout << "exit - выход из приложения;" << endl;
    }

    typedef double (*func)(double x);

    typedef double (*solv_func)(Equation &);

    static void print_equations() {
        std::cout << "Введите номер уравнения:" << std::endl;
        std::cout << "1: " << eq_1_str << std::endl;
        std::cout << "2: " << eq_2_str << std::endl;
        std::cout << "3: " << eq_3_str << std::endl;
    }

    static void print_methods() {
        std::cout << "Введите номер метода:" << std::endl;
        std::cout << "1: метод половинного деления" << std::endl;
        std::cout << "2: метод Ньютона" << std::endl;
        std::cout << "3: метод простых итераций" << std::endl;
    }

    static func select_equation() {
        int function = 1;
        print_equations();
        std::cin >> function;
        switch (function) {
            case 1:
                return func1;
            case 2:
                return func2;
            case 3:
                return func3;
            default:
                return func1;
        }
    }

    static func select_eq_der2(func function) {
        if (function == func1) {
            return func1_der2;
        } else if (function == func2) {
            return func2_der2;
        } else {
            return func3_der2;
        }
    }

    static func select_eq_der(func function) {
        if (function == func1) {
            return func1_der;
        } else if (function == func2) {
            return func2_der;
        } else {
            return func3_der;
        }
    }

    static solv_func select_method() {
        int method = 1;
        print_methods();
        std::cin >> method;
        switch (method) {
            case 1:
                return Equation::half_del_method;
            case 2:
                return Equation::newton_method;
            case 3:
                return Equation::simple_iter_method;
            default:
                return Equation::half_del_method;
        }
    }

    void nle_command(Console &console) {
        std::string filename;
        std::cout << "Введите имя файла, откуда читать интервал/погрешность:" << std::endl;
        getline(std::cin, filename);
        std::ifstream file;
        double start = 0;
        double finish = 0;
        double eps = 0.01;
        func object_func = select_equation();
        func object_der = select_eq_der(object_func);
        func object_der2 = select_eq_der2(object_func);
        solv_func object_solver = select_method();
        Equation equation(object_solver, object_func, object_der, object_der2);
        if (!filename.empty()) {
            file.open(filename, std::ifstream::in);
            file >> start;
            file >> finish;
            file >> eps;
        } else {
            std::cout << "Введите начало интервала:";
            std::cin >> start;
            std::cout << "Введите конец интервала:";
            std::cin >> finish;
            std::cout << "Введите погрешность:";
            std::cin >> eps;
        }
        equation.set_interval(start, finish);
        equation.set_eps(eps);
        bool is_valid = equation.root_validation(equation);
        if (!is_valid) {
            return;
        }
        equation.solve();
        std::cin.ignore();
    }

    static void print_systems() {
        std::cout << "Выберите одну из систем:" << std::endl;
        std::cout << "1: " << sys_1_1_str << std::endl;
        std::cout << "   " << sys_1_2_str << std::endl;
        std::cout << "2: " << sys_2_1_str << std::endl;
        std::cout << "   " << sys_2_2_str << std::endl;
    }

    static bool set_system(EquationsSystem &system) {
        print_systems();
        int sys_num;
        std::cin >> sys_num;
        switch (sys_num) {
            case 1:
                system.first = sys_func_11;
                system.second = sys_func_12;
                system.x_11 = sys_11_dx;
                system.y_11 = sys_11_dy;
                system.x_21 = sys_12_dx;
                system.y_21 = sys_12_dy;
                return true;
            case 2:
                system.first = sys_func_21;
                system.second = sys_func_22;
                system.x_11 = sys_21_dx;
                system.y_11 = sys_21_dy;
                system.x_21 = sys_22_dx;
                system.y_21 = sys_22_dy;
                return true;
            default:
                return false;
        }
    }

    void snle_command(Console &console) {
        std::string filename;
        std::cout << "Введите имя файла, откуда читать интервал/погрешность:" << std::endl;
        getline(std::cin, filename);
        std::ifstream file;
        EquationsSystem system;
        system.sys_matrix_init();
        bool valid = set_system(system);
        if (!valid) {
            std::cout << "Вы ввели неверный номер системы";
            return;
        }
        if (!filename.empty()) {
            file.open(filename, std::ifstream::in);
            file >> system.x0;
            file >> system.y0;
            file >> system.eps;
        } else {
            std::cout << "Введите x0:" << std::endl;
            std::cin >> system.x0;
            std::cout << "Введите y0:" << std::endl;
            std::cin >> system.y0;
            std::cout << "Введите точность:" << std::endl;
            std::cin >> system.eps;
            std::cin.ignore();
        }
        system.solve();
    }

    void exit_command(Console &console) {
        std::cout << "Производится выход из программы..." << std::endl;
    }

    void undefined_command(Console &console) {
        std::cout << "Такой команды не существует! Обратитесь к help, для справки по командам." << std::endl;
    }

    void UserCommand::parse_command(std::string &arg) {
        if (arg == "help") {
            this->callback = help_command;
        } else if (arg == "nle") {
            this->callback = nle_command;
        } else if (arg == "snle") {
            this->callback = snle_command;
        } else if (arg == "exit") {
            this->callback = exit_command;
        } else {
            this->callback = undefined_command;
        }
    }

    bool UserCommand::activate(common_utils::Console &console) const {
        if (callback != nullptr) {
            this->callback(console);
            return true;
        } else {
            std::cout << "Упс, что-то пошло не так..." << std::endl;
            return false;
        }
    }

    UserCommand::func UserCommand::get_callback() {
        return this->callback;
    }
} // common_utils