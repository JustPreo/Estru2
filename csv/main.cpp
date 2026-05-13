#include <iostream>
#include "CsvStudentRecord.hpp"
#include <vector>
#include <fstream>


int main(){
    
    std::cout<<"Ingresar archivo CSV: ";
    std::string nombreArchivo;
    std::getline(std::cin, nombreArchivo);
    std::fstream archivo;

    archivo.open(nombreArchivo, std::ios::in);
    if (!archivo.is_open()){
        std::cerr << "Error"<<"'\n'";
    }

    //saltar linea
    std::vector<CsvStudentRecord> estudiantes;
    std::string linea;
    std::getline(archivo,linea);//En teoria saltar primera linea?
    while (std::getline(archivo,linea)){
        std::vector<std::string> lineaVector;
        bool allow = true;
        std::string stringactual;
        //0 = id , 1 = nombre , 2 = float
        for (int i = 0;i < linea.length();i++){
            if (i == linea.length()-1){
                stringactual += linea[i];
                allow = true;
            }

            if ((linea[i]==',' && allow ) || ( i == (linea.length()-1) && allow) ){
                lineaVector.push_back(stringactual);//Porque ya termino la linea
                stringactual.clear();
                continue;
            }

            else if (linea[i]=='"'&& allow){
            allow = !allow;//Lo opuesto a lo que esta osea false
            continue;    
            }

            else if (linea[i]=='"' && !allow){//Cuando termina la cosa
                allow = !allow;
                continue;
            }//Lo tengo en 2 ifs porque lo miro mas ordenado

            stringactual += linea[i];

        }
        CsvStudentRecord temp;

        if (!lineaVector.size()!=0 && !lineaVector.size()==3){
            std::cerr << "Error" << "\n";        
        }

        temp.id = std::stoi(lineaVector[0]);
        temp.name=lineaVector[1];
        temp.nota = std::stof(lineaVector[2]);
        estudiantes.push_back(temp);
    }//Fin while

    for (CsvStudentRecord& stud : estudiantes){
        std::cout << "ID:"<< stud.id <<
        "|Name:"<<stud.name<<
        "|Nota:"<<stud.nota<<'\n';
    }





}