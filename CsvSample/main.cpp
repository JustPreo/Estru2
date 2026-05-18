#include "Methods.hpp"
#include "StudentRec.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "=== Prueba de serialize/deserialize ===\n";
    StudentRec original{42, "Ana Gómez", 9.5f};

    std::vector<char> data = Methods::serialize(original);
    std::cout << "Serializado: tamaño=" << data.size() << " bytes\n";

    StudentRec restored = Methods::deserialize(data);
    std::cout << "Deserializado: id=" << restored.id
              << ", name='" << restored.name << "'"
              << ", gpa=" << restored.gpa << "\n\n";

    std::cout << "=== Prueba CSVToBinary ===\n";
    const std::string csvPath = "test_students.csv";
    std::ofstream csvFile(csvPath);
    if (!csvFile) {
        std::cerr << "Error: no se pudo crear el archivo de prueba " << csvPath << "\n";
        return 1;
    }

    csvFile << "id,name,gpa\n";
    csvFile << "1,Juan Perez,8.25\n";
    csvFile << "2,\"Laura, Díaz\",7.90\n";
    csvFile.close();

    std::cout << "Archivo CSV de prueba creado: " << csvPath << "\n";

    Methods methods;
    methods.CSVToBinary(csvPath);

    std::cout << "CSV a binario completado. Archivo generado: students.dat\n";
    return 0;
}
