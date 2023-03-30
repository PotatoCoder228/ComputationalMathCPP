//
// Created by sasha on 29.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_USERCOMMAND_H
#define COMPUTATIONALMATHCPP_USERCOMMAND_H

#include <iostream>
#include "Console.h"

namespace common_utils {
    void help_command(Console &console);

    void nle_command(Console &console);

    void snle_command(Console &console);

    void exit_command(Console &console);

    void undefined_command(Console &console);

    class UserCommand {
        typedef void (*func)(Console &);

    private:
        func callback;
    public:
        void parse_command(std::string &arg);

        bool activate(Console &console) const;

        func get_callback();
    };
} // common_utils

#endif //COMPUTATIONALMATHCPP_USERCOMMAND_H
