cmake_minimum_required(VERSION 3.10)

project(RTSPServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(GST_RTSP_SERVER REQUIRED gstreamer-rtsp-server-1.0)
include_directories(${GST_INCLUDE_DIRS} ${GST_RTSP_SERVER_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS} ${GST_RTSP_SERVER_LIBRARY_DIRS})

set(SRC_DIR src)
file(GLOB_RECURSE SRC src/*)

add_executable(${PROJECT_NAME}
    ${SRC}
)

target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} ${GST_RTSP_SERVER_LIBRARIES})
