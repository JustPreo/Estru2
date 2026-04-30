#include <iostream>
#include <cstring>
#include "StudentFile.hpp"
#include "CliArgs.hpp"

using std::cin;
using std::cout;


int main(int argc, const char *argv[]) {

    CliArgs args(argc,argv);

    if (!args.isGood()){
        args.printUsage();
        return 1;
    }
    StudentFile st_file("students.dat");

    switch (args.cliCommand().value()){
        case CliCommand::ListStudents:
        std::cout<<"List"<<std::endl;
        
        
        if (st_file.open()) {
            StudentRecord temp;
            int contador = 1;
            
            std::cout << "\n--- Stdnt List ---\n";
            
            while (st_file.readRecord(temp)) {
                std::cout << "Register #" << contador++ << "\n";
                std::cout << "ID: " << temp.id << "\n0";
                std::cout << "Name: " << temp.nombre << "\n";
                std::cout << "Grade: " << temp.nota << "\n";
                std::cout << "---------------------------\n";
            }
        } else {
            std::cerr << "Error opening .dat\n";
        }
        break;
        
        case CliCommand::InsertStudent:
            st_file.open();

            StudentRecord s;
            
            cout << "ID: ";
            cin >> s.id;

            cout << "Name: ";
            cin.ignore();
            cin.getline(s.nombre, 64);//se cambia manual

            cout << "Grade: ";
            cin >> s.nota;
            
            st_file.writeRecord(s);


            break;
    }

    return 0;
}