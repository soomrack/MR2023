cmake_minimum_required(VERSION 3.15)

project(ads1115 VERSION 0.1 DESCRIPTION "Static library for usage ADS1115" LANGUAGES CXX)

include(CTest)
include(FindPkgConfig)
enable_testing()

# Dependency flags
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Constants
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD 17)

# Exporting commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX AND NOT APPLE)
        find_package(Threads REQUIRED)
endif()

include_directories(${PROJECT_NAME} ${PROJECT_INCLUDE_DIR})

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inc/ADS1115.h ${CMAKE_BINARY_DIR}/include/ADS1115.h COPYONLY)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX
                        VERSION ${PROJECT_VERSION} SOVERSION 1
                        PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/inc/ADS1115.h)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

if(UNIX AND NOT APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif()


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${USB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)










