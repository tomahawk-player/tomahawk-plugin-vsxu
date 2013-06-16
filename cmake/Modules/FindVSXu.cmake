# Find VSXU - Finds VSXu libraries.
#
# This module defines
#  VSXU_FOUND - whether the qsjon library was found
#  VSXU_LIBRARIES - the vsxu library
#  VSXU_INCLUDE_DIRS - the include path of the vsxu library
#

if ( NOT WIN32 )
    # use pkg-config to get the values of VSXU_INCLUDE_DIRS
    # and VSXU_LIBRARY_DIRS to add as hints to the find commands.
    include (FindPkgConfig)
    pkg_check_modules (VSXU libvsxu)
endif (NOT WIN32)


find_library (VSXU_ENGINE_LIBRARY
    NAMES
    vsxu_engine
    PATHS
    ${VSXU_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

message(STATUS "VSXU_ENGINE_LIBRARY: " ${VSXU_ENGINE_LIBRARY})

find_library (VSXU_ENGINE_GRAPHICS_LIBRARY
    NAMES
    vsxu_engine_graphics
    PATHS
    ${VSXU_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

message(STATUS "VSXU_ENGINE_GRAPHICS_LIBRARY: " ${VSXU_ENGINE_GRAPHICS_LIBRARY})

find_library (VSXU_ENGINE_AUDIOVISUAL_LIBRARY
    NAMES
    vsxu_engine_audiovisual
    PATHS
    ${VSXU_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

message(STATUS "VSXU_ENGINE_AUDIOVISUAL_LIBRARY: " ${VSXU_ENGINE_AUDIOVISUAL_LIBRARY})

find_path (VSXU_INCLUDE_DIRS
    NAMES
    vsxu_platform.h
    PATHS
    ${VSXU_INCLUDE_DIRS}
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
)

message(STATUS "VSXU_INCLUDE_DIRS: " ${VSXU_INCLUDE_DIRS})

set( VSXU_LIBRARIES ${VSXU_ENGINE_LIBRARY} ${VSXU_ENGINE_GRAPHICS_LIBRARY} ${VSXU_ENGINE_AUDIOVISUAL_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VSXu DEFAULT_MSG VSXU_LIBRARIES VSXU_INCLUDE_DIRS)
mark_as_advanced(VSXU_LIBRARIES VSXU_INCLUDE_DIRS)
