cmake_minimum_required(VERSION 3.20)

project(Containers CXX)
set(TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(${TARGET} main.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector
    ${CMAKE_CURRENT_SOURCE_DIR}/linked_list
)

target_sources(${TARGET} PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/vector.cpp
)

target_compile_options(${TARGET} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

