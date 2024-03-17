cmake_minimum_required(VERSION 3.9)

project(Test VERSION 1.1 DESCRIPTION "PriorityQueue" LANGUAGES CXX)

add_subdirectory(PriorityQueue)

add_executable(myexe main.cpp)

target_link_libraries(myexe PriorityQueue)