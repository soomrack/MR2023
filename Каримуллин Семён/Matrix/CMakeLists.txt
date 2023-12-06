#cmake_minimum_required(3.22.1)

project(matrix)

set(SOURSE_EXE main.c)

set(SOURCE_LIB Matrix.c)

add_library(matrix STATIC ${SOURCE_LIB})

add_executable(main ${SOURSE_EXE})

target_link_libraries(main matrix)