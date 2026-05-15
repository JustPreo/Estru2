cmake_minimum_required(VERSION 3.5)
project(StudentSerializerTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    doctest
    URL      https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.zip
    URL_HASH SHA256=6745e17682d6e2be1ea31ec8bf1814a3d7cb17d61d120e5f2ee5a075926634ad
)
FetchContent_MakeAvailable(doctest)

add_executable(test_runner test_student_serializer.cpp student_serializer.cpp)

target_include_directories(test_runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(test_runner PRIVATE doctest::doctest)

enable_testing()
add_test(NAME StudentSerializerTests COMMAND test_runner)
