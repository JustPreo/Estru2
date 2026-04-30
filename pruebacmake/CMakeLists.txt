cmake_minimum_required(VERSION 3.20)
project(pruebacmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prba main.cpp StudentRecord.hpp StudentFile.hpp StudentFile.cpp
    CliArgs.hpp CliArgs.cpp)  