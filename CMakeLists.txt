#
# This file was generated from CMakeLists.txt.in
#
# This file was copied and modified from https://cmake.org/examples/
#

cmake_minimum_required( VERSION 3.16 )

# rudimentary version handling by setting it manually in this file
set ( T8PIE_VERSION_MAJOR 1 )
set ( T8PIE_VERSION_MINOR 0 )
set ( T8PIE_VERSION_PATCH 0 )

project(
  T8PIE
  DESCRIPTION "A template for project that link against the t8code library."
  LANGUAGES C CXX
  VERSION "1.0.0"
)

#
# Enable "make test" to run all the tests
#
include( CTest )

# Set compilers to mpicc and mpicxx
set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)

# Searchers for t8code build with CMake
# To add a seach path use 
#  -DT8CODE_DIR=PATH,
#  -DP4EST_DIR=PATH,
#  -DSC_DIR=PATH,
find_package ( T8CODE REQUIRED)

# if t8code is linked against VTK, this project will
# automatically detect it and link against VTK as well.
# We set T8PIE_ENABLE_VTK to 1 in order to define our own VTK dependent macros in src/CMakeLists.txt
if (T8CODE_ENABLE_VTK)
    message ("t8code links against VTK with version ")
    set (T8PIE_ENABLE_VTK "1")
endif ()

# Recurse into the "src" subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (src)

# Add executable called "t8pie_helloworld" that is built from the source file
# "t8pie_main.cxx". The extensions are automatically found.
add_executable (t8pie_helloworld t8pie_main.cxx)

# Link the executable to the t8pie library. Since the library has
# public include directories we will use those link directories when building
# t8pie_demo.
target_link_libraries (t8pie_helloworld LINK_PUBLIC t8pie T8CODE::T8)

# Recurse into the "test" subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (test)
