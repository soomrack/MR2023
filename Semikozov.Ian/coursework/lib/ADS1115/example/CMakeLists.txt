cmake_minimum_required(VERSION 3.15)

project(example_ads)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ads1115)
