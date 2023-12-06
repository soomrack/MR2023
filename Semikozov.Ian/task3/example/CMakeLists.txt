cmake_minimum_required(VERSION 3.15)

project(example VERSION 0.1
                DESCRIPTION "Example usage of matrix library"
                LANGUAGES C)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE matrix)