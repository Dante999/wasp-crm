cmake_minimum_required(VERSION 3.15)

project(WaspCRM CXX)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# standard compiler warnings
add_library(project_warnings INTERFACE)
include(cmake/compiler-warnings.cmake)
set_project_warnings(project_warnings)

include(cmake/standard-project-settings.cmake)



add_subdirectory(code/utils)

#option(BULD_WITH_TESTS "Enable to build with tests", ON)
