cmake_minimum_required(VERSION 3.20)

project(Matrix)

set	(GROUP_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/
	)

include_directories(${GROUP_INCLUDES})

# Create a static library
add_library(${PROJECT_NAME}_lib STATIC
		matrix.h
		matrix.c
		)

target_include_directories(${PROJECT_NAME}_lib
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/)

	
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Examples)