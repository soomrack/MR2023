cmake_minimum_required(VERSION 3.6)
project(libabstract)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        src/dynamic_array.cpp
        src/dynamic_array.h
        src/linked_list.cpp
        src/linked_list.h
        src/queue.cpp
        src/queue.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_PATH}/src)