#include "Methods.hpp"
#include <algorithm>

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

