cmake_minimum_required(VERSION 3.6)
project(graph)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        src/parser.cpp
        src/parser.h
        src/builder.cpp
        src/builder.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_PATH}/src)