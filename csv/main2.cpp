#include <iostream>
#include <csv.h>
#include <string>
int main2(){
    //Pone columnas
    ios::CSVReader<3> in("students.csv")
    in.read_header(io::ignore_extra_column,"nombre","edad","gpa");
    std::string nombre;
    int edad;
    double gpa;

    while (in.read_row(nombre,edad,gpa)){
        std::cout << nombre << " " << gpa << "\n ";
    }
    return 0;
}
