cmake_minimum_required(VERSION 3.0.0)
project(MatrixHandler VERSION 0.1.0 LANGUAGES C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/inc/${PROJECT_NAME}.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.c)

set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

add_executable(Matrix src/main.c src/MatrixHandler.c)

target_link_libraries(${PROJECT_NAME} PRIVATE m)
target_link_libraries(Matrix PRIVATE m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})   
include(CPack)
    