cmake_minimum_required(VERSION 3.0.0)
project(MatrixHandler VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(${CMAKE_PROJECT_NAME} src/main.c src/MatrixHandler.c)

target_link_libraries(${PROJECT_NAME} m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
