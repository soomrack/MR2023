cmake_minimum_required(VERSION 3.22.0)
project(CxxMatrixHandler VERSION 0.1.0 LANGUAGES C CXX)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} src/matrixHandler.cpp src/main.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
