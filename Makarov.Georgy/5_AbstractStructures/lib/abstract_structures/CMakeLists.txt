cmake_minimum_required(VERSION 3.6)
project(abstract_structures)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        src/dynamic_array.cpp
        src/dynamic_array.h
        src/linked_list.cpp
        src/linked_list.h
        src/doubly_linked_list.cpp
        src/doubly_linked_list.h
        src/stack.h
        src/priority_linked_list.h
        src/priority_linked_list.cpp
        src/queue.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_PATH}/src)