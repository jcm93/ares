#[=======================================================================[.rst:
FindKosmicKrisp
-------

Finds the KosmicKrisp library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``KosmicKrisp::KosmicKrisp``
  The KosmicKrisp library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``KosmicKrisp_FOUND``
  True if the system has the KosmicKrisp library.
``KosmicKrisp_VERSION``
  The version of the SDL library which was found.
``KosmicKrisp_LIBRARIES``
  Libraries needed to link to KosmicKrisp.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``KosmicKrisp_LIBRARY``
  The path to the KosmicKrisp library.

#]=======================================================================]

# cmake-lint: disable=C0103

include(FindPackageHandleStandardArgs)


find_library(
  KosmicKrisp_LIBRARY
  NAMES vulkan_kosmickrisp
  DOC "KosmicKrisp library location"
)

find_file(
  KosmicKrisp_ICD_JSON
  NAMES share/vulkan/icd.d/kosmickrisp_mesa_icd.aarch64.json etc/vulkan/icd.d/kosmickrisp_mesa_icd.aarch64.json
  DOC "KosmicKrisp ICD JSON location"
)

set(
  KosmicKrisp_ERROR_REASON
  "Ensure that ares-deps is provided as part of CMAKE_PREFIX_PATH or that KosmicKrisp is present in local library paths."
)

find_package_handle_standard_args(
  KosmicKrisp
  REQUIRED_VARS KosmicKrisp_LIBRARY KosmicKrisp_ICD_JSON
  REASON_FAILURE_MESSAGE "${KosmicKrisp_ERROR_REASON}"
)
unset(KosmicKrisp_ERROR_REASON)
mark_as_advanced(KosmicKrisp_LIBRARY)

if(KosmicKrisp_FOUND)
  if(NOT TARGET KosmicKrisp::KosmicKrisp)
    if(IS_ABSOLUTE "${KosmicKrisp_LIBRARY}")
      add_library(KosmicKrisp::KosmicKrisp UNKNOWN IMPORTED)
      set_property(TARGET KosmicKrisp::KosmicKrisp PROPERTY IMPORTED_LOCATION "${KosmicKrisp_LIBRARY}")
    else()
      add_library(KosmicKrisp::KosmicKrisp SHARED IMPORTED)
      set_property(TARGET KosmicKrisp::KosmicKrisp PROPERTY IMPORTED_LIBNAME "${KosmicKrisp_LIBRARY}")
    endif()
    add_library(kk_resource INTERFACE)
    add_library(KosmicKrisp::Resources ALIAS kk_resource)
    target_sources(kk_resource PRIVATE "${KosmicKrisp_ICD_JSON}")
    set_property(TARGET kk_resource PROPERTY RESOURCE "${KosmicKrisp_ICD_JSON}")
    target_link_libraries(KosmicKrisp::KosmicKrisp INTERFACE KosmicKrisp::Resources)
    set_source_files_properties(${KosmicKrisp_ICD_JSON} PROPERTIES HEADER_FILE_ONLY TRUE)
  endif()
endif()

include(FeatureSummary)
set_package_properties(
  KosmicKrisp
  PROPERTIES
    URL "https://github.com/KhronosGroup/KosmicKrisp"
    DESCRIPTION
      "KosmicKrisp is a Vulkan Portability implementation. It layers a subset of the high-performance, industry-standard Vulkan graphics and compute API over Apple's Metal graphics framework, enabling Vulkan applications to run on macOS, iOS and tvOS."
)
