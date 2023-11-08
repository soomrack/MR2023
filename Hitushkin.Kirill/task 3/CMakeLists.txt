cmake_minimum_required(VERSION 3.2)

project(Matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_exe src/main.cpp)
add_library(Matrix src/matrix.cpp src/matrix.hpp)
target_link_libraries(my_exe PRIVATE Matrix)
