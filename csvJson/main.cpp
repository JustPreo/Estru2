#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "csv.h"
#include "CsvStudentRecord.hpp"

namespace nl = nlohmann;

namespace {
nl::json studentToJson(const CsvStudentRecord& student) {
    return {
        {"id", student.id},
        {"nombre", student.name},
        {"nota", student.nota}
    };
}
}

int main(int argc, char* argv[]) {
    // const std::string inputPath = argc > 1 ? argv[1] : "students.csv";
    // const std::string outputPath = argc > 2 ? argv[2] : "students.json";
    if (argc != 3){
        return 1;
    }
    const std::string inputPath = argv[1];
    const std::string outputPath = argv[2];
    // const std::string inputPath = "students_sample_500.csv";
    // const std::string outputPath = "students_sample_500.json";

    try {
        io::CSVReader<3> in(inputPath);//declaro el csv
        in.read_header(io::ignore_extra_column, "id", "nombre", "nota");//ignoramos la primerap arte

        std::vector<CsvStudentRecord> students;
        CsvStudentRecord student{};
        //estudiantes se crean y ahora se leen
        while (in.read_row(student.id, student.name, student.nota)) {
            students.push_back(student);//se crea estudiante
        }

        nl::json output = nl::json::array();//se crea un array json
        for (const auto& currentStudent : students) {
            output.push_back(studentToJson(currentStudent));
        }

        std::ofstream file(outputPath);
        if (!file) {
            std::cerr << "No se pudo crear el archivo JSON: " << outputPath << '\n';
            return 1;
        }

        file << output.dump(2) << '\n';
        std::cout << "Convertidos " << students.size() << " estudiantes a " << outputPath << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
