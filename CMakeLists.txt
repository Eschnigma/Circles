###########################################################
### CMAKE PROJECT FILE FOR BATTY BLAST ( working title ) ##
###########################################################

# ------------------------------ Basic project settings ------------------------------

cmake_minimum_required ( VERSION 2.8 )
project ( "Circles!" )


# ------------------------------ Compiler settings ------------------------------

set ( CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g"
)

# Add MinGW support for Windows
if ( MINGW )
    set ( MINGW32_LIBRARY
        mingw32
    )
endif ( MINGW )


# ------------------------------ Collect files and libs ------------------------------

# Library finding - location of shared libraries.

set ( EXT_SEARCHPATHS
	/usr
	/usr/local
	/opt
	/opt/local
)

# Library finding - location of the .cmake files
set ( CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/external/cmake_modules"
)

# Grab header files
include_directories ( ${CMAKE_SOURCE_DIR} )

# Source files
set ( SOURCES
  main.cpp
)


# ------------------------------ Find libraries ------------------------------

find_package ( SDL2 REQUIRED )


# ------------------------------ Build ------------------------------

# Create the game that will blow away the critics and revolutionize the industry.
add_executable ( circles ${SOURCES})
target_link_libraries (
    circles
    ${MINGW32_LIBRARY}
    ${SDL2MAIN_LIB}
    ${SDL2_DIR_LIB}
)
