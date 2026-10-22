#  This file is part of t8pie.
#  t8pie is a C library to manage a collection (a forest) of multiple
#  connected adaptive space-trees of general element types in parallel.
#
#  Copyright (C) 2025 the developers
#
#  t8pie is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  t8pie is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with t8pie; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

add_library( gtest /localdata1/holk_jo/coding/source/t8pie/../thirdparty/googletest-mpi/gtest/gtest-all.cc )
target_include_directories( gtest SYSTEM PUBLIC /localdata1/holk_jo/coding/source/t8pie/../thirdparty/googletest-mpi /localdata1/holk_jo/coding/source/t8pie/.. )


# Function to add a test executable and register it with CTest.
# The test executable is built from the provided source files.
function( add_t8pie_test )
    set( options "" )
    set( oneValueArgs "NAME" )
    set( multiValueArgs "SOURCES" )
    cmake_parse_arguments( ADD_T8PIE_TEST "" "" ""  )

    # Get the path of the first file listed in the SOURCES list and use it to determine the build directory.
    list (LENGTH ADD_T8PIE_TEST_SOURCES TEST_SOURCES_LENGTH)
    list(GET ADD_T8PIE_TEST_SOURCES 0 TEST_SOURCE)
    get_filename_component(TEST_SOURCE_DIR "/localdata1/holk_jo/coding/source/t8pie/" DIRECTORY)
    file(RELATIVE_PATH TEST_RELATIVE_DIR "/localdata1/holk_jo/coding/source/t8pie" "")
    set(TEST_BUILD_DIR "/localdata1/holk_jo/coding/source/t8pie/")

    add_executable(   )

    # Link base libraries.
    target_include_directories(  PRIVATE /localdata1/holk_jo/coding/source/t8pie/src )
    target_link_libraries(  PRIVATE t8pie T8CODE::T8 gtest pthread )

    set_target_properties( PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ""
        LIBRARY_OUTPUT_DIRECTORY ""
        ARCHIVE_OUTPUT_DIRECTORY ""
    )

    # Use "mpirun -np 4" as test command
    separate_arguments (T8PIE_TEST_COMMAND_LIST NATIVE_COMMAND "mpirun -np 4")
    add_test( NAME  COMMAND  / )
endfunction()

# Function to add a test executable for C++ tests.
# This function wraps the `add_t8pie_test` function to include common test sources.
# Common test sources are t8pie_gtest_main.cxx and t8pie_gtest_memory_macros.cxx
function ( add_t8pie_cpp_test)
    set( options "" )
    set( oneValueArgs "NAME" )
    set( multiValueArgs "SOURCES" )
    cmake_parse_arguments( ADD_T8PIE_CPP_TEST "" "" ""  )

    # add cpp sources to SOURCES list and call add_t8pie_test function
    list ( APPEND ADD_T8PIE_CPP_TEST_SOURCES t8pie_gtest_main.cxx )
    add_t8pie_test( NAME  SOURCES  )
endfunction()

add_t8pie_cpp_test( NAME t8pie_gtest_example     SOURCES t8pie_gtest_example.cxx )
add_t8pie_cpp_test( NAME t8pie_gtest_vtk_linkage SOURCES t8pie_gtest_vtk_linkage.cxx )
