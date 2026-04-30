#include <iostream>
#include "CliArgs.hpp"

void CliArgs::printUsage(){
    std::cout << "Usage" << program << "[--list-students | --insert-student]\n";
}

void CliArgs::parse(int argc, const char *argv[]){
    program = argv[0];

    if (argc >1 && argc <=2){
        std::string cdm = argv[1];

        if (cdm == "--list-students"){
            cli_command = CliCommand::ListStudents;
        }
        else if (cdm == "--insert-student"){
            cli_command = CliCommand::InsertStudent;
        }
        else {
            good = false;
        }

    }
    else {
        good = false;
    }

}