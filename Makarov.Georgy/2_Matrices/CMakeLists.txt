cmake_minimum_required(VERSION 3.6)
project(Matrices)

add_executable(${PROJECT_NAME}
        src/main.c
        src/matrices.c
        inc/matrices.h)

target_link_libraries(${PROJECT_NAME} PRIVATE m)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)