#[=======================================================================[.rst:
FindSparkle
-------

Finds the Sparkle library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``Sparkle::Sparkle``
  The Sparkle library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Sparkle_FOUND``
  True if the system has the Sparkle library.
``Sparkle_VERSION``
  The version of the Sparkle library which was found.
``Sparkle_INCLUDE_DIRS``
  Include directories needed to use Sparkle.
``Sparkle_LIBRARIES``
  Libraries needed to link to Sparkle.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Sparkle_INCLUDE_DIR``
  The directory containing ``Sparkle.h``.
``Sparkle_LIBRARY``
  The path to the Sparkle library.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_library(
  Sparkle_LIBRARY
  NAMES Sparkle
  DOC "Sparkle location"
)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin|Windows")
  set(Sparkle_ERROR_REASON "Ensure that ares-deps are provided as part of CMAKE_PREFIX_PATH.")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux|FreeBSD")
  set(Sparkle_ERROR_REASON "Ensure Sparkle libraries are available in local library paths.")
endif()

find_package_handle_standard_args(
  Sparkle
  REQUIRED_VARS Sparkle_LIBRARY
  VERSION_VAR Sparkle_VERSION
  REASON_FAILURE_MESSAGE "${Sparkle_ERROR_REASON}"
)
mark_as_advanced(Sparkle_INCLUDE_DIR Sparkle_LIBRARY)
unset(Sparkle_ERROR_REASON)

if(Sparkle_FOUND)
  if(NOT TARGET Sparkle::Sparkle)
    if(IS_ABSOLUTE "${Sparkle_LIBRARY}")
      add_library(Sparkle::Sparkle UNKNOWN IMPORTED)
      set_property(TARGET Sparkle::Sparkle PROPERTY IMPORTED_LOCATION "${Sparkle_LIBRARY}")
    else()
      add_library(Sparkle::Sparkle SHARED IMPORTED)
      set_property(TARGET Sparkle::Sparkle PROPERTY IMPORTED_LIBNAME "${Sparkle_LIBRARY}")
    endif()
  endif()
endif()

include(FeatureSummary)
set_package_properties(Sparkle PROPERTIES URL "https://github.com/sparkle-project/Sparkle" DESCRIPTION "A software update framework for macOS")
