cmake_minimum_required(VERSION 3.2)

project(Kapital)

add_executable(${PROJECT_NAME} Kapital.c)

target_link_libraries(Kapital m)