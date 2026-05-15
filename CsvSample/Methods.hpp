#include <iostream>
#include <string>
#include <vector>
#include "StudentRec.hpp"
#include <fstream>
#include "csv.h"

class Methods{
    public:
    Methods(){};
    static StudentRec deserialize(const std::vector<char>& buf);
    static std::vector<char> serialize(const StudentRec& rec);
    void CSVToBinary(std::string file_path);
    ~Methods() {};
    
};