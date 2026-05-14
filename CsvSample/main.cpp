#include "csv.h"
#include <iostream>
#include <string>
#include "Methods.hpp"
#include "StudentRec.hpp"
using MyCSVReader = io::CSVReader<4,io::trim_chars<' '>,io::double_quote_escape<',','\"'>>;

int main(){
    // MyCSVReader in("sample1.csv");
    // in.read_header(io::ignore_extra_column, "nombre","edad","gpa","activo");
    
    // std::string nombre;
    // int edad;
    // double gpa;
    // std::string activo;
    // while (in.read_row(nombre ,edad,gpa,activo)){
    //     std::cout << nombre << " | " << edad << " | " << gpa << '\n';
    // }

    Methods met("sample1.csv");
    StudentRec r;
    r.name = "Aaron";
    r.id = 1;
    r.gpa=0.00;
    
    met.serialize();
    

    return 0;
}