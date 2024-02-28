option(BUILD_SHARED_LIBS "Build DynamicArray shared library" OFF)

add_library(DynamicArray)

target_compile_features(DynamicArray PUBLIC cxx_std_14)

target_include_directories(
    DynamicArray
  PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_sources(
    DynamicArray
  PRIVATE 
    DynamicArray.cpp
)

install(
  TARGETS DynamicArray
  EXPORT DynamicArrayTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/DynamicArray
  DESTINATION include
)

install(
  EXPORT DynamicArrayTargets
  FILE DynamicArrayTargets.cmake
  NAMESPACE DynamicArray::
  DESTINATION lib/cmake/DynamicArray
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/DynamicArrayConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DynamicArray
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DynamicArrayConfigVersion.cmake"
  VERSION "${DynamicArray_VERSION_MAJOR}.${DynamicArray_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/DynamicArrayConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DynamicArrayConfigVersion.cmake"
  DESTINATION lib/cmake/DynamicArray
)

export(
  EXPORT DynamicArrayTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/DynamicArrayTargets.cmake"
  NAMESPACE DynamicArray::
)
