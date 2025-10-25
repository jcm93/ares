#[=======================================================================[.rst:
FindVulkan
-------

Finds the Vulkan library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``Vulkan::Vulkan``
  The Vulkan library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Vulkan_FOUND``
  True if the system has the Vulkan library.
``Vulkan_VERSION``
  The version of the SDL library which was found.
``Vulkan_LIBRARIES``
  Libraries needed to link to Vulkan.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Vulkan_LIBRARY``
  The path to the Vulkan library.

#]=======================================================================]

# cmake-lint: disable=C0103

set(frameworks_temp ${CMAKE_FIND_FRAMEWORK})
set(CMAKE_FIND_FRAMEWORK LAST)
include(FindPackageHandleStandardArgs)


find_library(
  Vulkan_LIBRARY
  NAMES vulkan.1.4.328
  DOC "Vulkan loader location"
)

set(
  Vulkan_ERROR_REASON
  "Ensure that ares-deps is provided as part of CMAKE_PREFIX_PATH or that the Vulkan loader is present in local library paths."
)

find_package_handle_standard_args(
  Vulkan
  REQUIRED_VARS Vulkan_LIBRARY
  REASON_FAILURE_MESSAGE "${Vulkan_ERROR_REASON}"
)
unset(Vulkan_ERROR_REASON)
mark_as_advanced(Vulkan_LIBRARY)

if(Vulkan_FOUND)
  if(NOT TARGET Vulkan::Vulkan)
    if(IS_ABSOLUTE "${Vulkan_LIBRARY}")
      add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
      set_property(TARGET Vulkan::Vulkan PROPERTY IMPORTED_LOCATION "${Vulkan_LIBRARY}")
    else()
      add_library(Vulkan::Vulkan SHARED IMPORTED)
      set_property(TARGET Vulkan::Vulkan PROPERTY IMPORTED_LIBNAME "${Vulkan_LIBRARY}")
    endif()
  endif()
endif()

include(FeatureSummary)
set_package_properties(
  Vulkan
  PROPERTIES
    URL "https://github.com/KhronosGroup/Vulkan"
    DESCRIPTION
      "Vulkan is a Vulkan Portability implementation. It layers a subset of the high-performance, industry-standard Vulkan graphics and compute API over Apple's Metal graphics framework, enabling Vulkan applications to run on macOS, iOS and tvOS."
)

set(CMAKE_FIND_FRAMEWORK ${frameworks_temp})
