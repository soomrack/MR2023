cmake_minimum_required(VERSION 3.5)

project(sort LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp sort.cpp)