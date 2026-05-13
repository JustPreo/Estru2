#include <cstdint>
#include <string>

struct StudentRec
{
    uint32_t id;
    std::string name;
    float gpa;
};

// StudentRec sr;

// //Serializacion de reistros de tamano variable

// uint32_t totalSize = sizeof(uint32_t) * 2 + sr.name.length() + sizeof(float);

// std::vector<char> record(totalSize);

// char *p = record.data();
// *reinterpret_cast<uint32_t *>(p) = totalSize;
// p+= sizeof(uint32_t);

// *reinterpret_cast<uint32_t *>(p) = sr.id;
// p+=sizeof)(uint32_t);

// std::copy(sr.name.begin,sr.name.end,p);
// p+= sr.name.length();

// *reinterpret_cast<float *>(p) = sr.gpa;

// out.write(record.data(),record.size());

//Deserealizacion de registro de tamano variable

//leer el total size
//in.read

// std::vector<char> record(totalSize);
// in.read(record.data(),record.size());

// StudentRec sr;

// char *p = record.data()+sizeof(uint32_t);

// sr.id = reinterpret_cast<int *>(p);
// p += sizeof(uint32_t);
// uint32_t nameL = totalSize - sizeof(uint32_t)*2 - sizeof(float);
// sr.name = std::string(p , p+nameL);
// p+=nameL;

// sr.nota = *reinterpret_cast<float *>(p);

//Hacer una clase , poner le metodo serialized y deserialized