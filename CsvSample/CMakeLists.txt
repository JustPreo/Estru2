cmake_minimum_required(VERSION 3.20)
project(CsvSample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prba main.cpp
    Methods.cpp
    StudentRec.hpp
    Methods.hpp)  