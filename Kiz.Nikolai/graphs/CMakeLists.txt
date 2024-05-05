cmake_minimum_required(VERSION 3.22.1)
project(DjikstraAirlanes VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/parser)
set(GRAPH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/graph)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/graph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


file(GLOB_RECURSE HEADERS ${PARSER_DIR}/*.hpp ${GRAPH_DIR}/*.hpp)
file(GLOB_RECURSE SRCS ${PARSER_DIR}/*.cpp ${GRAPH_DIR}/*.cpp)


add_compile_options(-fsanitize=leak)
add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS} main.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
