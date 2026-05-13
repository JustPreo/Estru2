#include <iostream>
#include <string>
#include <vector>
#include "StudentRec.hpp"
#include <fstream>

class Methods{
    public:
    Methods(std::string fp) : file_path(fp) {}
    std::vector<char> Serial();
    void DeSerial(StudentRec& sr);
    ~Methods() {};

    private:
    std::fstream in_out;
    std::string file_path;
}