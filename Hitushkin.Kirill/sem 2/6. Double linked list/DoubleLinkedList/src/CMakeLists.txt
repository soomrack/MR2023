option(BUILD_SHARED_LIBS "Build DoubleLinkedList shared library" OFF)

add_library(DoubleLinkedList)

target_compile_features(DoubleLinkedList PUBLIC cxx_std_14)

target_include_directories(
    DoubleLinkedList
  PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_sources(
    DoubleLinkedList
  PRIVATE 
    DoubleLinkedList.cpp
)

install(
  TARGETS DoubleLinkedList
  EXPORT DoubleLinkedListTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/DoubleLinkedList
  DESTINATION include
)

install(
  EXPORT DoubleLinkedListTargets
  FILE DoubleLinkedListTargets.cmake
  NAMESPACE DoubleLinkedList::
  DESTINATION lib/cmake/DoubleLinkedList
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/DoubleLinkedListConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DoubleLinkedList
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DoubleLinkedListConfigVersion.cmake"
  VERSION "${DoubleLinkedList_VERSION_MAJOR}.${DoubleLinkedList_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/DoubleLinkedListConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DoubleLinkedListConfigVersion.cmake"
  DESTINATION lib/cmake/DoubleLinkedList
)

export(
  EXPORT DoubleLinkedListTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/DoubleLinkedListTargets.cmake"
  NAMESPACE DoubleLinkedList::
)
