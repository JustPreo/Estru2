cmake_minimum_required(VERSION 3.20)
project(pruebacmake)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(prba main.cpp CsvStudentRecord.hpp csv.h)

target_link_libraries(prba PRIVATE nlohmann_json::nlohmann_json)
