cmake_minimum_required(VERSION 3.20)

project(Graph CXX)
set(target ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(${target})

target_include_directories(${target} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${target} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/graph.cpp
)

target_compile_options(${target} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-Og>
    # $<$<CONFIG:Release>:-Og -g0>
)
