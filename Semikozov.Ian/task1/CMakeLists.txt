cmake_minimum_required(VERSION 3.15)

project(alicebob)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} m)