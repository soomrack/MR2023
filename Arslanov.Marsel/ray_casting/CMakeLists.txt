cmake_minimum_required(VERSION 3.20)

project(ray_casting CXX)

set(target ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(${target} main.cpp)

target_include_directories(${target} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vecs
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${target} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/shapes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/scene.cpp
)
