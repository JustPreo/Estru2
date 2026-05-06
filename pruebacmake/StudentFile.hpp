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
        bool writeRecordEOF(const StudentRecord &student_r);
        bool writeRecord(const StudentRecord &student_r);
        bool readRecord(StudentRecord &student_r);
        void seekTo(std::streampos pos);

    private:
        std::string filepath_;
        std::fstream in_out;
    };