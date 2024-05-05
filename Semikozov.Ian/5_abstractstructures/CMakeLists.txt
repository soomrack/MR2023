cmake_minimum_required(VERSION 3.20)

project(structures LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
file(GLOB source_list ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(${PROJECT_NAME} STATIC ${source_list})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable(example main.cpp)

target_link_libraries(example PRIVATE structures)