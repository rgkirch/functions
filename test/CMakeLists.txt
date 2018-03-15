cmake_minimum_required(VERSION 3.9)
project(functions)

include_directories("../src")
add_subdirectory("googletest")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

add_executable(functions functionsTest.cpp)
target_link_libraries(functions gtest gtest_main gmock)

#sudo update-alternatives --config c++