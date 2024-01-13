cmake_minimum_required(VERSION 3.22.0)
project(CxxMatrixHandler VERSION 0.1.0 LANGUAGES CXX)




add_executable(${PROJECT_NAME} matrixHandler.cpp example.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
