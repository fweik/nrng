cmake_minimum_required(VERSION 3.15)

project(nrng CXX)

# The exported library
add_library(nrng INTERFACE)
add_library(nrng::nrng ALIAS nrng)
target_include_directories(nrng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(nrng INTERFACE cxx_std_20)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(cmake/StandardProjectSettings.cmake)
  include(cmake/PreventInSourceBuilds.cmake)

  # Link this 'library' to set the c++ standard / compile-time options requested
  add_library(project_options INTERFACE)

  # Link this 'library' to use the warnings specified in CompilerWarnings.cmake
  add_library(project_warnings INTERFACE)

  # enable cache system
  include(cmake/Cache.cmake)

  # standard compiler warnings
  include(cmake/CompilerWarnings.cmake)
  set_project_warnings(project_warnings)

  # sanitizer options if supported by compiler
  include(cmake/Sanitizers.cmake)
  enable_sanitizers(project_options)

  # enable doxygen
  include(cmake/Doxygen.cmake)
  enable_doxygen()

  # allow for static analysis options
  include(cmake/StaticAnalyzers.cmake)

  # Add co-shipped dependencies
  add_subdirectory(external)

  enable_testing()
  message("Building Tests.")
  add_subdirectory(tests)
endif()
