#include "csv.h"
#include <iostream>
#include <string>
#include "Methods.hpp"
#include "StudentRec.hpp"
using MyCSVReader = io::CSVReader<4,io::trim_chars<' '>,io::double_quote_escape<',','\"'>>;

int main(){
    //Sample.dat

    Methods me;
    std::vector<StudentRec> totalRecord;
    me.CSVToBinary("students_sample_500.csv");

    return 0;
}