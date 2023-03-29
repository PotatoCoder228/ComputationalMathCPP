//
// Created by sasha on 29.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_USERCOMMAND_H
#define COMPUTATIONALMATHCPP_USERCOMMAND_H

#include <iostream>
#include "Console.h"

namespace common_utils {
    class UserCommand {
    private:
        void (*callback)(Console&);
    public:
        void parse_command(std::string& arg);
        static void help_command(Console& console);
        static void nle_command(Console& console);
        static void snle_command(Console& console);
        static void exit_command(Console& console);
        static void undefined_command(Console& console);
        bool activate(Console& console) const;
        void (*get_callback())(Console&);
    };
} // common_utils

#endif //COMPUTATIONALMATHCPP_USERCOMMAND_H
