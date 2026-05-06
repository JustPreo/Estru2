#include "StudentFile.hpp"

bool StudentFile::open()
{
    in_out.open(filepath_,std::ios::binary | std::ios::in | std::ios::out);


    return in_out.is_open();
}

bool StudentFile::writeRecordEOF(const StudentRecord &student_r) {
    if (!in_out.is_open()) return false;
    in_out.seekp(0,std::ios::end);
    in_out.write(reinterpret_cast<const char *>(&student_r), sizeof(StudentRecord));
    return in_out.good(); 
}

bool StudentFile::writeRecord(const StudentRecord &student_r) {
    if (!in_out.is_open()) return false;
    in_out.write(reinterpret_cast<const char *>(&student_r), sizeof(StudentRecord));
    return in_out.good(); 
}

bool StudentFile::readRecord(StudentRecord &student_r) {
    if (!in_out.is_open()) return false;
    in_out.read(reinterpret_cast<char *>(&student_r), sizeof(StudentRecord));
  
    return in_out.gcount() == sizeof(StudentRecord);
}

void StudentFile::seekTo(std::streampos pos) {
    in_out.clear();
    in_out.seekg(pos);
    in_out.seekp(pos);
}