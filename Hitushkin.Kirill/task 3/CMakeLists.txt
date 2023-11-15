cmake_minimum_required(VERSION 3.20)

message("Building with CMake version: ${CMAKE_VERSION}")

project(Matrix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_exe src/main.cpp)
add_library(Matrix src/matrix.cpp src/matrix.hpp)
target_link_libraries(my_exe PRIVATE Matrix)