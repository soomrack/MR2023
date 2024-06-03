cmake_minimum_required(VERSION 3.20)

project(Containers CXX)
set(TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(${TARGET} main.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE DEBUG)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector
    ${CMAKE_CURRENT_SOURCE_DIR}/single_linked_list
    ${CMAKE_CURRENT_SOURCE_DIR}/list
    ${CMAKE_CURRENT_SOURCE_DIR}/stack
    ${CMAKE_CURRENT_SOURCE_DIR}/priority_queue
)

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector/array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/single_linked_list/single_linked_list.cpp
)

target_compile_options(${TARGET} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Release>:-Og -g0>
)

