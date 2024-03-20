option(BUILD_SHARED_LIBS "Build Graph shared library" OFF)

add_library(Graph)

target_compile_features(Graph PUBLIC cxx_std_20)

target_include_directories(
    Graph
  PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_sources(
    Graph
  PRIVATE 
    Graph.cpp
)

install(
  TARGETS Graph
  EXPORT GraphTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/Graph
  DESTINATION include
)

install(
  EXPORT GraphTargets
  FILE GraphTargets.cmake
  NAMESPACE Graph::
  DESTINATION lib/cmake/Graph
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/GraphConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Graph
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GraphConfigVersion.cmake"
  VERSION "${Graph_VERSION_MAJOR}.${Graph_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/GraphConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GraphConfigVersion.cmake"
  DESTINATION lib/cmake/Graph
)

export(
  EXPORT GraphTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/GraphTargets.cmake"
  NAMESPACE Graph::
)
