#[=======================================================================[.rst:
FindSDL
-------

Finds the SDL library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``cairo::cairo``

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``cairo_FOUND``
  True if the system has cairo.
``cairo_VERSION``
  The version of cairo which was found.
``cairo_INCLUDE_DIRS``
  Include directories needed to use cairo.
``cairo_LIBRARIES``
  Libraries needed to link to cairo.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:
.
``cairo_LIBRARY``
  The path to the cairo library..

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(PC_cairo QUIET cairo)
endif()

find_path(
  cairo_INCLUDE_DIRS
  NAMES cairo.h cairo/cairo.h
  HINTS ${PC_cairo_INCLUDE_DIRS}
  PATHS /usr/include /usr/local/include /usr/include/cairo
  DOC "cairo include directory"
)

find_library(
  cairo_LIBRARY
  NAMES cairo
  HINTS ${PC_cairo_LIBRARY_DIRS}
  PATHS /usr/lib /usr/local/lib
  DOC "cairo location"
)

set(cairo_ERROR_REASON "Ensure cairo libraries are available in local library paths.")

find_package_handle_standard_args(
  cairo
  REQUIRED_VARS cairo_LIBRARY cairo_INCLUDE_DIRS
  VERSION_VAR cairo_VERSION
  REASON_FAILURE_MESSAGE "${cairo_ERROR_REASON}"
)
mark_as_advanced(cairo_INCLUDE_DIRS cairo_LIBRARY)
unset(cairo_ERROR_REASON)

if(cairo_FOUND)
  if(NOT TARGET cairo::cairo)
    if(IS_ABSOLUTE "${cairo_LIBRARY}")
      add_library(cairo::cairo UNKNOWN IMPORTED)
      set_property(TARGET cairo::cairo PROPERTY IMPORTED_LOCATION "${cairo_LIBRARY}")
    else()
      add_library(cairo::cairo SHARED IMPORTED)
      set_property(TARGET cairo::cairo PROPERTY IMPORTED_LIBNAME "${cairo_LIBRARY}")
    endif()

    message(AUTHOR_WARNING "interface compile options ${PC_cairo_CFLAGS_OTHER}, interface include directories ${cairo_INCLUDE_DIRS}, version ${cairo_VERSION}")
    set_target_properties(
      cairo::cairo
      PROPERTIES
        INTERFACE_COMPILE_OPTIONS "${PC_cairo_CFLAGS_OTHER}"
        INTERFACE_INCLUDE_DIRECTORIES "${cairo_INCLUDE_DIRS}"
    )
  endif()
endif()


include(FeatureSummary)
set_package_properties(cairo PROPERTIES URL "https://www.cairographics.org/" DESCRIPTION "Cairo is an open-source graphics library that provides a vector graphics-based, device-independent API for software developers.")
