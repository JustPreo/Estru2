#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
struct StudentRec
{
    uint32_t    id;
    std::string name;
    float       nota;
};

// ─────────────────────────────────────────────────────────────────────────────
// Wire format (native-endian integers, IEEE 754 float)
//
//  ┌──────────────────┬───────────┬────────────────────┬──────────┐
//  │ total_size:u32   │  id:u32   │  name bytes        │ nota:f32 │
//  └──────────────────┴───────────┴────────────────────┴──────────┘
//   4 B                4 B         name.size() B         4 B
//
//  total_size = 4 (id) + name.size() + 4 (nota)
//  name_len   = total_size - 8          (deduced on deserialize)
// ─────────────────────────────────────────────────────────────────────────────
class StudentSerializer
{
public:
    static std::vector<char> serialize(const StudentRec& rec);
    static StudentRec deserialize(const std::vector<char>& buf);

private:
};
