cmake_minimum_required(VERSION 3.15)

project(matrix  VERSION 0.1 
                DESCRIPTION "Library to work with matrix"
                LANGUAGES CXX)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrix.cpp)
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrix.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/matrix.hpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/matrix.hpp ${CMAKE_BINARY_DIR}/include/matrix.hpp COPYONLY)

set_target_properties(${PROJECT_NAME} PROPERTIES
                        LINKER_LANGUAGE CXX
                        VERSION ${PROJECT_VERSION}
                        SOVERSION 1
                        PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/matrix.hpp)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_BINARY_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PRIVATE -fvisibility=hidden)
target_link_libraries(${PROJECT_NAME} PRIVATE m)
add_subdirectory(example)