cmake_minimum_required(VERSION 3.6)
project(graph_example)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} cmake-build-debug/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE graph)
