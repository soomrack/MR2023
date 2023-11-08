#cmake_minimum_required(VERSION 3.21)
project(matrix)

#set(CMAKE_CXX_STANDARD 20)

add_library(libmy STATIC libmy.c)
add_executable(test 01.c)

target_link_libraries(test libmy)
