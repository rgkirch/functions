cmake_minimum_required(VERSION 3.9)

#set(CXX_FLAGS "-g --std=c++17")
set(CMAKE_CXX_STANDARD 17)

add_executable(option_test option_test.cpp)
target_link_libraries(option_test)
