#include "StudentFIle.hpp"

bool StudentFile::open()
{
    in_out.open(filepath_,std::ios::binary | std::ios::in | std::ios::out);


    return in_out.is_open();
}

bool StudentFile::writeRecord(const StudentRecord &student_r)
{
    if (!in_out.is_open()){
        return false;
    }

    in_out.write(reinterpret_cast<char *>(&student_r),sizeof(StudentRecord));



    return in_out.good;
}

bool StudentFile::readRecord(StudentRecord &student_r)
{
    if (!in_out.is_open()){
        return false;
    }

    in_out.read(reinterpret_cast<char *>(&student_r),sizeof(StudentRecord));
    return (in_out.gcount() == sizeof(StudentRecord));
}