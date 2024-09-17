cmake_minimum_required(VERSION 3.10)

project(OmegabotManualControl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set(SRC_DIR src)
file(GLOB_RECURSE SRC src/*)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-video-1.0)
pkg_check_modules(SDL2 REQUIRED sdl2)


include_directories(${GST_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS} ${SDL2_LIBRARY_DIRS})

add_executable(${PROJECT_NAME}
    ${SRC}
)

target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} ${SDL2_LIBRARIES})
