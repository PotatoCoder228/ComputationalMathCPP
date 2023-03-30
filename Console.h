//
// Created by sasha on 29.03.2023.
//

#ifndef COMPUTATIONALMATHCPP_CONSOLE_H
#define COMPUTATIONALMATHCPP_CONSOLE_H

#include <vector>

namespace common_utils {

    class Console {
    private:
        bool is_running;
    public:
        void run();

        void init();
    };

} // common_utils

#endif //COMPUTATIONALMATHCPP_CONSOLE_H
