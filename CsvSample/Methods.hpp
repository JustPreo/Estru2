#include <iostream>
#include <string>
#include <vector>
#include "StudentRec.hpp"
#include <fstream>

class Methods{
    public:
    Methods(std::string fp) : file_path(fp) {}
    static StudentRec deserialize(const std::vector<char>& buf);
    static std::vector<char> serialize(const StudentRec& rec);
    ~Methods() {};

    private:
    std::fstream in_out;
    std::string file_path;
};