cmake_minimum_required(VERSION 3.9)

project(Test VERSION 1.1 DESCRIPTION "Graph" LANGUAGES CXX)

add_subdirectory(Graph)

add_executable(myexe main.cpp)

target_link_libraries(myexe Graph)