#[=======================================================================[.rst:
Findchd-rs
-------

Finds the chd-rs library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``chd-rs::chd-rs``
  The chd-rs library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``chd-rs_FOUND``
  True if the system has the libarashader library.
``chd-rs_VERSION``
  The version of the SDL library which was found.
``chd-rs_INCLUDE_DIR``
  Include directories needed to use chd-rs.
``chd-rs_LIBRARIES``
  Libraries needed to link to chd-rs.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``chd-rs_INCLUDE_DIR``
  The directory containing ``chd.h``.
``chd-rs_LIBRARY``
  The path to the chd-rs library.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(PC_chd-rs chd-rs)
endif()

find_path(
  chd-rs_INCLUDE_DIR
  NAMES chd.h libchdr/chd.h
  HINTS ${PC_chd-rs_INCLUDE_DIRS} ${_chd-rs_path_hint}
  PATHS /usr/include /usr/local/include
  DOC "chd-rs include directory"
)
message(AUTHOR_WARNING "chdrs include dir is ${chd-rs_INCLUDE_DIR}")

if(PC_chd-rs_VERSION VERSION_GREATER 0)
  set(chd-rs_VERSION ${PC_chd-rs_VERSION})
else()
  if(NOT chd-rs_FIND_QUIETLY)
    message(AUTHOR_WARNING "Failed to find chd-rs version.")
  endif()
  set(chd-rs_VERSION 0.0.0)
endif()

find_library(
  chd-rs_LIBRARY
  NAMES libchd_capi chd_capi
  HINTS ${PC_chd-rs_LIBRARY_DIRS}
  PATHS /usr/lib /usr/local/lib
  DOC "chd-rs location"
)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin|Windows")
  set(chd-rs_ERROR_REASON "Ensure that ares-deps is provided as part of CMAKE_PREFIX_PATH.")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux|FreeBSD")
  set(chd-rs_ERROR_REASON "Ensure chd-rs libraries are available in local library paths.")
endif()

find_package_handle_standard_args(
  chd-rs
  REQUIRED_VARS chd-rs_LIBRARY
  VERSION_VAR chd-rs_VERSION
  REASON_FAILURE_MESSAGE "${chd-rs_ERROR_REASON}"
)
mark_as_advanced(chd-rs_INCLUDE_DIR chd-rs_LIBRARY)
unset(chd-rs_ERROR_REASON)

if(chd-rs_FOUND)
  if(NOT TARGET chd-rs::chd-rs)
    add_library(chd-rs::chd-rs UNKNOWN IMPORTED)
    set_property(TARGET chd-rs::chd-rs PROPERTY IMPORTED_LOCATION "${chd-rs_LIBRARY}")
    # cargo does not set the minimum version correctly in the dylib, so manually define chd-rs's actual system requirement
    set_property(TARGET chd-rs::chd-rs PROPERTY MACOS_VERSION_REQUIRED 10.15)

    set_target_properties(
      chd-rs::chd-rs
      PROPERTIES
        INTERFACE_COMPILE_OPTIONS "${PC_chd-rs_CFLAGS_OTHER}"
        INTERFACE_INCLUDE_DIRECTORIES "${chd-rs_INCLUDE_DIR}"
        VERSION ${chd-rs_VERSION}
    )
  endif()
endif()

include(FeatureSummary)
set_package_properties(
  chd-rs
  PROPERTIES
    URL "https://github.com/SnowflakePowered/chd-rs"
    DESCRIPTION
      "Pure Rust implementation of the Compressed Hunks of Data format, drop-in for libchdr."
)
