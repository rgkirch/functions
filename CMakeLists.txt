cmake_minimum_required(VERSION 3.7)
project(functions)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(treeSum treeSum.cpp)
add_executable(cons cons.cpp)
add_executable(sum sum.cpp)
#set(SOURCE_FILES main.cpp library.h)
#add_library(functions ${SOURCE_FILES})