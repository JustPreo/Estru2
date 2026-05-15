#include "student_serializer.hpp"

std::vector<char> StudentSerializer::serialize(const StudentRec& sr)
{
    std::fstream in_out;
    in_out.open("sample.dat", std::ios::binary | std::ios::out);

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

    *reinterpret_cast<float *>(p) = sr.nota;

    in_out.write(record.data(),record.size());

    return record;
}

StudentRec StudentSerializer::deserialize(const std::vector<char>& record)
{

    StudentRec sr;
    const char* p = record.data() + sizeof(int);
    sr.id = *reinterpret_cast<const uint32_t *>(p);
    p += sizeof(uint32_t);

    size_t nameL = record.size() - sizeof(int) - sizeof(uint32_t) - sizeof(float);
    sr.name.assign(p, nameL);
    p += nameL;

    sr.nota = *reinterpret_cast<const float *>(p);
    return sr;

}
