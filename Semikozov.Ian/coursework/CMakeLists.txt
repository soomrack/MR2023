cmake_minimum_required(VERSION 3.15)
project(CubeSat-Stand VERSION 0.2)

if(UNIX AND NOT APPLE)
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)
endif()

# Constants
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/*.hpp)

# Exporting commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC bytestorm ads1115 MotorRequests)

if(UNIX AND NOT APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common ${PROJECT_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/include)