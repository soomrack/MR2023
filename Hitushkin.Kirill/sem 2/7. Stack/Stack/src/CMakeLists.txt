option(BUILD_SHARED_LIBS "Build Stack shared library" OFF)

add_library(Stack INTERFACE)

target_include_directories(
    Stack
  INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

install(
  TARGETS Stack
  EXPORT StackTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/Stack
  DESTINATION include
)

install(
  EXPORT StackTargets
  FILE StackTargets.cmake
  NAMESPACE Stack::
  DESTINATION lib/cmake/Stack
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/StackConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Stack
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/StackConfigVersion.cmake"
  VERSION "${Stack_VERSION_MAJOR}.${Stack_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/StackConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/StackConfigVersion.cmake"
  DESTINATION lib/cmake/Stack
)

export(
  EXPORT StackTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/StackTargets.cmake"
  NAMESPACE Stack::
)
