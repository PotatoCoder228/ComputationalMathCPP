//
// Created by sasha on 29.03.2023.
//

#include "UserCommand.h"

namespace common_utils {
    void UserCommand::help_command(Console &console){
        using std::cout;
        using std::endl;
        cout<<"help - справка по командам;"<<endl;
        cout<<"nle - решение НУ;"<<endl;
        cout<<"snle - решение СНУ;"<<endl;
        cout<<"exit - выход из приложения;"<<endl;
    }

    void UserCommand::nle_command(Console &console) {

    }

    void UserCommand::snle_command(Console &console){

    }

    void UserCommand::exit_command(Console &console){
        std::cout << "Производится выход из программы..." << std::endl;
    }

    void UserCommand::undefined_command(Console &console) {
        std::cout<<"Такой команды не существует! Обратитесь к help, для справки по командам."<<std::endl;
    }

    void UserCommand::parse_command(std::string & arg) {
        if(arg=="help"){
            this->callback = &UserCommand::help_command;
        }
        else if(arg == "nle"){
            this->callback = &UserCommand::nle_command;
        }
        else if(arg == "snle"){
            this->callback = &UserCommand::snle_command;
        }
        else if(arg == "exit"){
            this->callback = &UserCommand::exit_command;
        }
        else{
            this->callback = &UserCommand::undefined_command;
        }
    }
    bool UserCommand::activate(common_utils::Console& console) const {
        if(callback != nullptr){
            this->callback(console);
            return true;
        }
        else{
            std::cout<<"Упс, что-то пошло не так..."<<std::endl;
            return false;
        }
    }

    void (*(UserCommand::get_callback()))(Console&) {
        return this->callback;
    }
} // common_utils