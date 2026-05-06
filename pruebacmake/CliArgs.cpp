#include <iostream>
#include "CliArgs.hpp"
#include <fstream>   

void CliArgs::printUsage(){
    std::cout << "Usage" << program << "--file <student file path> "
              << "[--list-students | --insert-student | --search-student <student id> | --remove-student <student id>]\n";
            }


void CliArgs::parse(int argc, const char *argv[]) {
    program = argv[0];
    good = true;

    if (argc < 3 || argc > 5) {//Solo valid si args == 3 o == 4
        std::cerr << "Error: Invalid number of arguments\n";
        good = false;
        return;
    }
    //bools pa despues
    bool has_file = false;
    bool has_command = false;


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];//arg va a hacer referencia a los argumentos valga la redundancia

        //primera iteracion
        if (arg == "--file") {
            if (has_file) {
                std::cerr << "Error: Can't provide --file as second arg\n";
                good = false;
                return;
            }

            if (i + 1 >= argc) {
                std::cerr << "Error: Missing file path after --file\n";
                good = false;
                return;
            }

            filepath_ = argv[++i];
            has_file = true;
        }
        //tercera iteracion
        else if (arg == "--list-students") {
            if (has_command) {
                std::cerr << "Error: Multiple commands provided\n";
                good = false;
                return;
            }

            cli_command = CliCommand::ListStudents;
            has_command = true;
        }

        else if (arg == "--insert-student") {
            if (has_command) {
                std::cerr << "Error: Multiple commands provided\n";
                good = false;
                return;
            }

            cli_command = CliCommand::InsertStudent;
            has_command = true;
        }

        else if (arg == "--search-student") {
            if (has_command) {
                std::cerr << "Error: Multiple commands provided\n";
                good = false;
                return;
            }

            if (i + 1 >= argc) {
                std::cerr << "Error: Missing student ID after --search-student\n";
                good = false;
                return;
            }

            try {
                student_id_ = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Error: Invalid student ID (must be a number)\n";
                good = false;
                return;
            }

            cli_command = CliCommand::SearchStudent;
            has_command = true;
        }
        else if (arg == "--remove-student") {
            if (has_command) {
                std::cerr << "Error: Multiple commands provided\n";
                good = false;
                return;
            }
            if (i + 1 >= argc) {
                std::cerr << "Error: Missing student ID after --remove-student\n";
                good = false;
                return;
            }

            try {
                student_id_ = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Error: Invalid student ID (must be a number)\n";
                good = false;
                return;
            }

            cli_command = CliCommand::RemoveStudent;
            has_command = true;
        }

        else {
            std::cerr << "Error: Unknown argument -> " << arg << "\n";
            good = false;
            return;
        }
    }

    //si la primera iteracion no es file
    if (!has_file) {
        std::cerr << "Error: --file is required\n";
        good = false;
        return;
    }

    if (!has_command) {
        std::cerr << "Error: A command is required\n";
        good = false;
        return;
    }

    //if (cli_command != CliCommand::InsertStudent) { Tenia pensado hacerlo para que ceara faile pero futuro
        std::ifstream file(filepath_);
        if (!file.good()) {
            std::cerr << "Error: File does not exist or cannot be opened\n";
            good = false;
            return;
        }
    //}
}

