#include <iostream>
#include "csv.h"
#include <string>

int main(){
    //Pone columnas
    io::CSVReader<3> in("students.csv");
    in.read_header(io::ignore_extra_column, "Id", "Nombre", "Nota");

    int id;
    std::string nombre;
    double nota;

    while (in.read_row(id, nombre, nota)){
        std::cout << "ID: " << id << " | Nombre: " << nombre << " | Nota: " << nota << "\n";
    }

    return 0;
}
