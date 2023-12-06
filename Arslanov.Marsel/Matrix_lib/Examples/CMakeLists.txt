cmake_minimum_required(VERSION 3.20)

project(Matrix)

# set (SOURCES_FILES 
#         main.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${PROJECT_NAME}_lib)