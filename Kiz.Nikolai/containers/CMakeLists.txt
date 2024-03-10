cmake_minimum_required(VERSION 3.22.1)
project(containers VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/linked_list/inc)
include_directories(${CMAKE_SOURCE_DIR}/linked_list/src)



add_executable(containers main.cpp)

set(CMAKE_CXX_FLAGS "-g -fsanitize=leak")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
