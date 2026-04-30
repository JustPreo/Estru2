#pragma once
#include "StudentRecord.hpp"

#include <string>
#include <fstream>

class StudentFile{
    public:
    StudentFile(const std::string& filepath): filepath_(filepath)
        {}

        ~StudentFile(){
            in_out.close();
        }
        bool open();
        bool writeRecord(const StudentRecord &student_r);
        bool readRecord(StudentRecord &student_r);

    private:
        std::string filepath_;
        std::fstream in_out;
    };