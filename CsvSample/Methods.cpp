#include "Methods.hpp"
#include <algorithm>

std::vector<char> Methods::serialize(const StudentRec& sr)
{
    int totalSize = sizeof(int) + sizeof(int) + sr.name.size() + sizeof(float);
    std::vector<char> record(totalSize);
    char* p = record.data();

    *reinterpret_cast<int*>(p) = totalSize;
    p+=sizeof(int);

    *reinterpret_cast<int*>(p) = sr.id;
    p+=sizeof(int);

    std::copy(sr.name.begin(),sr.name.end(),p);
    p+=sr.name.size();

    *reinterpret_cast<float*>(p) = sr.gpa;

    return record;
}

StudentRec Methods::deserialize(const std::vector<char>& record)
{
    StudentRec sr;
    const char* p = record.data();
    int totalSize = *reinterpret_cast<const int*>(p);
    p+=sizeof(int);

    sr.id = *reinterpret_cast<const int*>(p);
    p+= sizeof(int);

    int namel = totalSize - sizeof(int)*2 - sizeof(float);

    sr.name = std::string(p,namel);
    p+= namel;

    sr.gpa = *reinterpret_cast<const float*>(p);

    return sr;

}
void Methods::CSVToBinary(std::string file_path){
    std::ifstream file(file_path);
    std::string line;

    std::vector<StudentRec> srList;
    //saltar la linea
    std::getline(file,line);
    while (std::getline(file,line)){
        bool CommasAllowed = false;
        std::string current = "";
        std::vector<std::string> SrParameters;
        for (int i = 0;i < line.length();i++){
            char c = line[i];
            if(c == '"'){
                CommasAllowed = !CommasAllowed;
            }
            else if (c == ',' && !CommasAllowed){
                //osea si no se permiten comas pue
                SrParameters.push_back(current);
                current.clear();
            }
            else {
                current+=c;
            }

            

        }
    SrParameters.push_back(current);

    //id(int) , name , gpa(float)
    StudentRec sr;
    sr.id = std::stoi(SrParameters[0]);
    sr.name = SrParameters[1];
    sr.gpa = std::stof(SrParameters[2]);
    srList.push_back(sr);
    }

    //AHora escritura

    for (StudentRec sr: srList){
        std::vector<char> record = serialize(sr);
        std::ofstream out("students.dat",std::ios::binary|std::ios::app);
        out.write(record.data(),record.size());

        out.close();
    }
    
}

/*
std::vector<char> Methods::serialize(const StudentRec& sr)
{
    std::fstream in_out;
    in_out.open("sample.dat", std::ios::binary | std::ios::out | std::ios::app);

    //Serializacion de reistros de tamano variable

    uint32_t totalSize = sizeof(uint32_t) + sr.name.length() + sizeof(float);

    std::vector<char> record(totalSize + sizeof(uint32_t));

    char *p = record.data();
    *reinterpret_cast<uint32_t *>(p) = totalSize;
    p+= sizeof(uint32_t);

    *reinterpret_cast<uint32_t *>(p) = sr.id;
    p+=sizeof(uint32_t);

    std::copy(sr.name.begin(),sr.name.end(),p);
    p+= sr.name.length();

    *reinterpret_cast<float *>(p) = sr.gpa;

    in_out.write(record.data(),record.size());

    return record;
}

StudentRec Methods::deserialize(const std::vector<char>& record)
{

    StudentRec sr;
    const char* p = record.data() + sizeof(int);
    sr.id = *reinterpret_cast<const uint32_t *>(p);
    p += sizeof(uint32_t);

    size_t nameL = record.size() - sizeof(int) - sizeof(uint32_t) - sizeof(float);
    sr.name.assign(p, nameL);
    p += nameL;

    sr.gpa = *reinterpret_cast<const float *>(p);
    return sr;

}


void Methods::CSVToBinary(std::string file_path){
    io::CSVReader<3,io::trim_chars<' '>,io::double_quote_escape<',','\"'>> in(file_path);
    in.read_header(io::ignore_extra_column,"id","nombre","nota");
    int id;
    std::string nombre;
    double nota;

    std::vector<StudentRec> record;

    //Cosas que hacer:
    //Agregar el coso para que , lea archivo csv y al mismo tiempo escriba al binario 
    //o
    //Que tenga un vector con todos los StudentRecord y despues lo cree en un enodfile write

    StudentRec tmp;
    while (in.read_row(id,nombre,nota)){
        tmp.id=id;
        tmp.name=nombre;

        tmp.gpa=nota;

        record.push_back(tmp);
        
    }
    std::cout << "Termino de leer csv."<<'\n';


    for (StudentRec r:record){
        serialize(r);
    }
    std::cout << "Termino de pasar a binario."<<'\n';


    
}

*/