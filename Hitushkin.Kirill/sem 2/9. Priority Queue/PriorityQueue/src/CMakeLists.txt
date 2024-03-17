option(BUILD_SHARED_LIBS "Build PriorityQueue shared library" OFF)

add_library(PriorityQueue INTERFACE)

target_include_directories(
    PriorityQueue
  INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

install(
  TARGETS PriorityQueue
  EXPORT PriorityQueueTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/PriorityQueue
  DESTINATION include
)

install(
  EXPORT PriorityQueueTargets
  FILE PriorityQueueTargets.cmake
  NAMESPACE PriorityQueue::
  DESTINATION lib/cmake/PriorityQueue
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/PriorityQueueConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PriorityQueue
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PriorityQueueConfigVersion.cmake"
  VERSION "${PriorityQueue_VERSION_MAJOR}.${PriorityQueue_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/PriorityQueueConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/PriorityQueueConfigVersion.cmake"
  DESTINATION lib/cmake/PriorityQueue
)

export(
  EXPORT PriorityQueueTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/PriorityQueueTargets.cmake"
  NAMESPACE PriorityQueue::
)
