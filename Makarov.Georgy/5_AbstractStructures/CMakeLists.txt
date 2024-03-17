cmake_minimum_required(VERSION 3.6)
project(abstract_structures_example)

add_subdirectory(lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC abstract_structures)
