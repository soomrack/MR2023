cmake_minimum_required(VERSION 3.2)

project(Matrix)

add_executable(my_exe src/main.c)
add_library(Matrix src/matrix.c src/matrix.h)
target_link_libraries(my_exe PRIVATE Matrix)
