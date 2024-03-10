cmake_minimum_required(VERSION 3.6)
project(libmatrix_example)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE libmatrix)
