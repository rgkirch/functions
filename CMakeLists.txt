cmake_minimum_required(VERSION 3.9)
project(functions)

include_directories(src)
add_subdirectory(lib)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)
