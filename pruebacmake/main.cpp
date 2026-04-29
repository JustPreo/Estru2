#include <iostream>
#include "StudentRecord.hpp"
#include "StudentFile.cpp"
#include <cstddef>
#include <cstring>
#include <fstream>

using std::cout;

int main(){

    Student student;

    student.id = 1;
    strcpy(student.nombre, "Fernando Madrid");
    student.nota = 25;

    std::ofstream out("students.dat", std::ios::trunc);
    if(!out.is_open()){
        std::cerr << "Cannot create file 'students.dat'\n";
        return 1;
    }
    out.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    out.close();

    cout << "Successfully loaded!\n";



    StudentFile st_file(students.dat);
    _

    return 0;


}