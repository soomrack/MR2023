option(BUILD_SHARED_LIBS "Build Queue shared library" OFF)

add_library(Queue INTERFACE)

target_include_directories(
    Queue
  INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

install(
  TARGETS Queue
  EXPORT QueueTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/Queue
  DESTINATION include
)

install(
  EXPORT QueueTargets
  FILE QueueTargets.cmake
  NAMESPACE Queue::
  DESTINATION lib/cmake/Queue
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/QueueConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Queue
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/QueueConfigVersion.cmake"
  VERSION "${Queue_VERSION_MAJOR}.${Queue_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/QueueConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/QueueConfigVersion.cmake"
  DESTINATION lib/cmake/Queue
)

export(
  EXPORT QueueTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/QueueTargets.cmake"
  NAMESPACE Queue::
)
