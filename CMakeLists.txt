cmake_minimum_required(VERSION 2.8)
CMAKE_POLICY(SET CMP0017 NEW)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

set(QT_USE_QTOPENGL TRUE)

if(NOT TOMAHAWK_LIBRARIES)
    message(STATUS "BUILDING OUTSIDE TOMAHAWK")
    find_package(Tomahawk REQUIRED)
else()
    message(STATUS "BUILDING INSIDE TOMAHAWK")
    set(TOMAHAWK_USE_FILE "${CMAKE_SOURCE_DIR}/TomahawkUse.cmake")
endif()
include( ${TOMAHAWK_USE_FILE} )

include_directories( ${TOMAHAWK_INCLUDE_DIRS} )

find_package(VSXu REQUIRED)
include_directories( ${VSXU_INCLUDE_DIRS} )

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )


tomahawk_add_plugin(vsxu
    TYPE infoplugin
    EXPORT_MACRO INFOPLUGINDLLEXPORT_PRO
    SOURCES
        VSXuPlugin.cpp
        VisualizerWidget.cpp
        VSXuRenderer.cpp
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
        ${VSXU_LIBRARIES}
        ${QT_QTOPENGL_LIBRARIES}
        ${OPENGL_LIBRARIES}
)
