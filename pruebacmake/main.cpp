#include <iostream>
#include <cstring>
#include "StudentFile.hpp"
#include "CliArgs.hpp"
#include <format>

using std::cin;
using std::cout;


int main(int argc, const char *argv[]) {

    CliArgs args(argc,argv);

    if (!args.isGood()){
        args.printUsage();
        return 1;
    }
    StudentFile st_file(args.getFilePath());
    StudentRecord s;
    std::string st_name;

    switch (args.cliCommand().value()){
        case CliCommand::ListStudents:
            std::cout << "List" << std::endl;
            
            if (st_file.open()) {
                StudentRecord temp;
                int contador = 1;
                
                std::cout << "\n--- Stdnt List ---\n";
                
                while (st_file.readRecord(temp)) {
                    if (temp.id != -1){
                        std::cout << std::format(
                        "Register #{}\n"
                        "ID: {}\n"
                        "Name: {}\n"
                        "Grade: {:.2f}\n" // limita a dos decimales
                        "---------------------------\n",
                        contador++, temp.id, temp.nombre, temp.nota
                    );
                    }
                }
            }
            break;
        
        case CliCommand::InsertStudent:
             if (!st_file.open()){
                std::cerr << "Error opening .dat\n";
                break;
             }

            cout << "ID: ";
            cin >> s.id;

            cout << "Name: ";
            cin.ignore();
            std::getline(cin,st_name);//se cambia manual
            //Getline es hasta el enter sin importar el espacio
            try {
                if (st_name.length ()> sizeof(s.nombre)-1){
                throw std::runtime_error(std::format("Name too long.Max length: {}", sizeof(s.nombre)-1));
            }
            }catch(const std::runtime_error& err){
                std::cerr << err.what() << "\n";
                return 1;
            }
            
            

            std::copy(st_name.begin(),st_name.end(),&s.nombre[0]);
            //COpy desde begining hasta end , destino 
            s.nombre[st_name.length()] = '\0';

            cout << "Grade: ";
            cin >> s.nota;
            
            st_file.writeRecordEOF(s);


            break;
        case CliCommand::SearchStudent: {
            int t = 1;
            int id = args.getStudentId().value();
            bool found = false;

            st_file.open();
            StudentRecord temp_s;
            while (st_file.readRecord(temp_s)){
                if (temp_s.id == id){
                std::cout << std::format(
                        "ID: {}\n"
                        "Name: {}\n"
                        "Grade: {:.2f}\n" 
                        "---------------------------\n",
                        temp_s.id, temp_s.nombre, temp_s.nota
                    );
                    found = true;
                        break;
            }
            t++;
            }
            if (!found){std::cout << "Student not found\n";}
                
            break;}
        case CliCommand::RemoveStudent:{
            int i = 0;
            int idS = args.getStudentId().value();
            bool found = false;
            if (!st_file.open()){
            std::cerr << "Error opening file\n";
            return 1;
            }
            StudentRecord tmp;

            while(st_file.readRecord(tmp)){
                if (tmp.id == idS){
                    tmp.id = -1;
                    std::streampos pos = i * sizeof(StudentRecord);
                    st_file.seekTo(pos);
                    st_file.writeRecord(tmp);
                    found = true;
                    //como tal no perma del , pero para ponerlo como borrado
                    break;
                }
                i++;
            }
            if (!found){std::cout << "Student not found\n";}
            //Por si no lo encuentra
            
            break;}
    return 0;
}
}