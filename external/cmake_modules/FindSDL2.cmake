include(FindPackageHandleStandardArgs)

# ------------------------------ Update search path ------------------------------
# If using Mingw32 on Windows, we'll also search our local directory
if ( MINGW )
    set ( EXT_SEARCHPATHS
        ${EXT_SEARCHPATHS}
        ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.3/i686-w64-mingw32
    )
endif ( MINGW )


# ------------------------------ Find the includes ------------------------------

find_path ( SDL2_DIR_INCLUDE SDL.h
    PATH_SUFFIXES
        include
        include/SDL2
    PATHS
        ${EXT_SEARCHPATHS}
)


# ------------------------------ Find the libraries ------------------------------

# Main
find_library ( SDL2_DIR_LIB
    NAMES SDL2
    PATH_SUFFIXES
        lib
        lib64
    PATHS
        ${EXT_SEARCHPATHS}
)

# SDL2main
if ( NOT SDL2_BUILDING_LIBRARY )
    if ( NOT ${SDL2_DIR_INCLUDE} MATCHES ".framework" )

        find_library ( SDL2MAIN_LIB
            NAMES SDL2main
            PATH_SUFFIXES
                lib
                lib64
            PATHS
                ${EXT_SEARCHPATHS}
        )
    endif ( NOT ${SDL2_DIR_INCLUDE} MATCHES ".framework" )

    if ( SDL2MAIN_LIB )
        set ( SDL_DIR_LIB ${SDL2MAIN_LIB} ${SDL2_DIR_LIB})
    endif ( SDL2MAIN_LIB )

endif ( NOT SDL2_BUILDING_LIBRARY )

# Link Mingw32 if needed
if ( MINGW32 )
    set ( SDL2_DIR_LIB ${MINGW32_LIBRARY} ${SDL2_DIR_LIB} )
endif ( MINGW32 )


# ------------------------------ Add headers to project ------------------------------

include_directories (
    ${SDL2_DIR_INCLUDE}
)


# ------------------------------ Pass back to find_package ------------------------------

find_package_handle_standard_args (
    SDL2            # Name
    DEFAULT_MSG     # Print a message upon failure
    # Vars that need to be valid for find_package to succeed:
    SDL2_DIR_INCLUDE
    SDL2_DIR_LIB
)
