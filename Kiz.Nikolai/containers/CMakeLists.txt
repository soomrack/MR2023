cmake_minimum_required(VERSION 3.22.1)
project(containers VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true    ${CMAKE_CURRENT_SOURCE_DIR}/linked_list
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/stack
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/priority_queue)


foreach(INCLUDE_DIR ${INCLUDE_DIRS})
    include_directories(${INCLUDE_DIR})
endforeach()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})


file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(CMAKE_CXX_FLAGS "-g")
add_compile_options(-fsanitize=leak)

add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS} main.cpp)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


