cmake_minimum_required(VERSION 3.22)

project(sorting)

set(TARGET ${PROJECT_NAME})

set(SOURCES
    ${CMAKE_SOURCE_DIR}/source/sorting.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

set(INCLUDES
    ${CMAKE_SOURCE_DIR}/include
)

set(LIBRARIES
    array_sort
)

include_directories(${INCLUDES})

add_executable(${TARGET}
    ${SOURCES}
)

# target_include_directories(${TARGET} PRIVATE
#     ${INCLUDES}
# )

# add_subdirectory(Array_sort)

# target_link_libraries(${TARGET} PRIVATE
#     ${LIBRARIES}
# )