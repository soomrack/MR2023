cmake_minimum_required(VERSION 3.9)

project(Test VERSION 1.1 DESCRIPTION "Linked List" LANGUAGES CXX)

add_subdirectory(DoubleLinkedList)

add_executable(myexe main.cpp)

target_link_libraries(myexe DoubleLinkedList)