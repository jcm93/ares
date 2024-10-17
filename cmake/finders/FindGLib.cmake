#[=======================================================================[.rst:
FindSDL
-------

Finds the SDL library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``GLib::GLib``

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``GLib_FOUND``
  True if the system has GLib 3.
``GLib_VERSION``
  The version of GLib3 which was found.
``GLib_INCLUDE_DIRS``
  Include directories needed to use GLib3.
``GLib_LIBRARIES``
  Libraries needed to link to GLib3.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:
.
``GLib_LIBRARY``
  The path to the SDL library.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(PC_GLib QUIET glib-2.0)
endif()

message(AUTHOR_WARNING "PC glib include dirs are ${PC_GLib_INCLUDE_DIRS}")

find_path(
  GLib_INCLUDE_DIRS
  NAMES glib.h glib/glib.h
  HINTS ${PC_GLib_INCLUDE_DIRS}
  PATHS /usr/include /usr/local/include /usr/include/glib-2.0
  DOC "GLib include directory"
)

message(AUTHOR_WARNING "glib include dirs are ${GLib_INCLUDE_DIRS}")

find_library(
  GLib_LIBRARY
  NAMES glib GLib glib-2.0
  HINTS ${PC_GLib_LIBRARY_DIRS}
  PATHS /usr/lib /usr/local/lib
  DOC "GLib location"
)

set(GLib_ERROR_REASON "Ensure GLib libraries are available in local library paths.")

find_package_handle_standard_args(
  GLib
  REQUIRED_VARS GLib_LIBRARY GLib_INCLUDE_DIRS
  VERSION_VAR GLib_VERSION
  REASON_FAILURE_MESSAGE "${GLib_ERROR_REASON}"
)
mark_as_advanced(GLib_INCLUDE_DIRS GLib_LIBRARY)
unset(GLib_ERROR_REASON)

if(GLib_FOUND)
  if(NOT TARGET GLib::GLib)
    if(IS_ABSOLUTE "${GLib_LIBRARY}")
      message(AUTHOR_WARNING "adding unknown")
      add_library(GLib::GLib UNKNOWN IMPORTED)
      set_property(TARGET GLib::GLib PROPERTY IMPORTED_LOCATION "${GLib_LIBRARY}")
    else()
      message(AUTHOR_WARNING "adding shared")
      add_library(GLib::GLib SHARED IMPORTED)
      set_property(TARGET GLib::GLib PROPERTY IMPORTED_LIBNAME "${GLib_LIBRARY}")
    endif()

    set_target_properties(
      GLib::GLib
      PROPERTIES
        INTERFACE_COMPILE_OPTIONS "${PC_GLib_CFLAGS_OTHER}"
        INTERFACE_INCLUDE_DIRECTORIES "${PC_GLib_INCLUDE_DIRS}"
    )
  endif()
endif()

include(FeatureSummary)
set_package_properties(GLib PROPERTIES URL "https://docs.gtk.org/glib/" DESCRIPTION "GLib is a general-purpose, portable utility library, which provides many useful data types, macros, type conversions, string utilities, file utilities, a mainloop abstraction, and so on.")
