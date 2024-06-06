cmake_minimum_required(VERSION 3.6)

cmake_minimum_required(VERSION 3.6)
project(graph)

find_package(Boost 1.83 REQUIRED)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/inc ${Boost_INC})

add_executable(graph_example main.cpp)

target_link_libraries(graph_example PRIVATE graph)
