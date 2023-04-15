//
// Created by sasha on 29.03.2023.
//

#include <iostream>
#include "Console.h"
#include "UserCommand.h"

namespace common_utils {
    static const std::string GREETING(
            "████──████──███──████──███──████──████──████──████───███──████──████──████──████\n█──█──█──█───█───█──█───█───█──█──█──█──█──█──█──██──█────█──█──█──█──█──█──█──█\n████──█──█───█───████───█───█──█──█─────█──█──█──██──███──████────██────██──████\n█─────█──█───█───█──█───█───█──█──█──█──█──█──█──██──█────█─█───██────██────█──█\n█─────████───█───█──█───█───████──████──████──████───███──█─█───████──████──████");
    static const std::string INPUT_ERR_MSG("Некорректный ввод, попробуйте снова.");

    void Console::init() {
        std::cout << GREETING << std::endl;
    }

    void Console::run() {
        using std::cin;
        using std::cout;
        this->is_running = true;
        while (this->is_running) {
            std::string command;
            cout << "??";
            std::cin >> command;
            if (command.empty()) {
                cout << INPUT_ERR_MSG << std::endl;
                continue;
            }
            using common_utils::UserCommand;
            UserCommand arg;
            arg.parse_command(command);
            arg.activate(*this);
            if (arg.get_callback() == exit_command) {
                is_running = false;
                continue;
            }
        }
    }
} // common_utils