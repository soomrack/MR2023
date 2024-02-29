option(BUILD_SHARED_LIBS "Build LinkedList shared library" OFF)

add_library(LinkedList)

target_compile_features(LinkedList PUBLIC cxx_std_14)

target_include_directories(
    LinkedList
  PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_sources(
    LinkedList
  PRIVATE 
    LinkedList.cpp
)

install(
  TARGETS LinkedList
  EXPORT LinkedListTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/LinkedList
  DESTINATION include
)

install(
  EXPORT LinkedListTargets
  FILE LinkedListTargets.cmake
  NAMESPACE LinkedList::
  DESTINATION lib/cmake/LinkedList
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/LinkedListConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LinkedList
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/LinkedListConfigVersion.cmake"
  VERSION "${LinkedList_VERSION_MAJOR}.${LinkedList_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/LinkedListConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LinkedListConfigVersion.cmake"
  DESTINATION lib/cmake/LinkedList
)

export(
  EXPORT LinkedListTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/LinkedListTargets.cmake"
  NAMESPACE LinkedList::
)
