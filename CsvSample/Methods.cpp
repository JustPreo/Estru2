#include "Methods.hpp"
#include <algorithm>

std::vector<char> Methods::Serial(){
    in_out.open(file_path, std::ios::binary | std::ios::out);
StudentRec sr;

//Serializacion de reistros de tamano variable

uint32_t totalSize = sizeof(uint32_t) + sr.name.length() + sizeof(float);

std::vector<char> record(totalSize + sizeof(uint32_t));

char *p = record.data();
*reinterpret_cast<uint32_t *>(p) = totalSize;
p+= sizeof(uint32_t);

*reinterpret_cast<uint32_t *>(p) = sr.id;
p+=sizeof)(uint32_t);

std::copy(sr.name.begin,sr.name.end,p);
p+= sr.name.length();

*reinterpret_cast<float *>(p) = sr.gpa;

out.write(record.data(),record.size());


}

void Methods::DeSerial(StudentRec& sr){

}

