#
# This is the CMake file for the src subfolder.
# It defines the library to build.
#

# Create a library called "t8pie" which includes the source files.
# The extension is already found. Any number of sources could be listed here.
add_library (t8pie t8pie_helloworld.cxx)

# Link library against t8code, p4est, sc
target_link_libraries (t8pie PRIVATE T8CODE::T8 )

# Make sure the compiler can find include files for our t8pie library
# when other libraries or executables link to t8pie
target_include_directories (t8pie PUBLIC /localdata1/holk_jo/coding/source/t8pie)

# Add headers files to install in /include folder
install( FILES
    t8pie_helloworld.hxx
    TYPE INCLUDE
)

# VTK dependent settings.
if( T8PIE_ENABLE_VTK )
    set ( T8PIE_VTK_VERSION_USED "." )
    if (NOT  STREQUAL )
        message (FATAL_ERROR "VTK version mismatch. t8code uses  and this project uses .")
    endif ()
    # Set CMake variables for lib target

    # Define T8PIE_VTK_VERSION_USED for internal and external use in source files.
    # Note, external libraries linking against t8code (i.e. using find_package ( T8CODE REQUIRED )) can
    # use T8PIE_VTK_VERSION_USED in source code and in CMake scripts (triggered by config.cmake.in).
    target_compile_definitions( t8pie PUBLIC T8PIE_VTK_VERSION_USED="" )
    target_compile_definitions( t8pie PUBLIC T8PIE_ENABLE_VTK=1 )
    target_include_directories( t8pie PUBLIC  )
    target_link_libraries( t8pie PUBLIC  )
    # Internal source files that need VTK linkage to compile:
#    target_sources(T8PIE PRIVATE
#     put/source/file/here
#    )
#    
    # Installed header files that need VTK linkage:
#    install( FILES
#     put/header/file/here
#    DESTINATION include)
endif()

# Make this package available as a cmake install package, so 
# that other projects can find it with find_package.
include( CMakePackageConfigHelpers )

configure_package_config_file( /localdata1/holk_jo/coding/source/t8pie/config.cmake.in
  /localdata1/holk_jo/coding/source/t8pie/CMakeFiles/T8PIEConfig.cmake
INSTALL_DESTINATION cmake
)

write_basic_package_version_file(
/localdata1/holk_jo/coding/source/t8pie/CMakeFiles/T8PIEConfigVersion.cmake
COMPATIBILITY SameMajorVersion
VERSION "1.0.0"
)

install(FILES /localdata1/holk_jo/coding/source/t8pie/CMakeFiles/T8PIEConfig.cmake
              /localdata1/holk_jo/coding/source/t8pie/CMakeFiles/T8PIEConfigVersion.cmake
        DESTINATION /cmake )

install( TARGETS t8pie LIBRARY )

#
