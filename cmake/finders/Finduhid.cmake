#[=======================================================================[.rst:
Finduhid
-------

Finds the usbhid library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``uhid::uhid``

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``uhid_FOUND``
  True if the system has uhid.
``uhid_LIBRARIES``
  The location of the usbhid library.
``uhid_INCLUDE_DIR``
  Include directories needed to use uhid.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_path(
  uhid_INCLUDE_DIR
  NAMES usbhid.h /dev/usb/usbhid.h
  PATHS /usr/include /usr/local/include
  DOC "uhid include directory"
)

find_library(
  uhid_LIBRARIES
  NAMES usbhid
  PATHS /usr/lib /usr/local/lib
  DOC "uhid location"
)

set(uhid_VERSION ${CMAKE_HOST_SYSTEM_VERSION})

find_package_handle_standard_args(
  uhid
  REQUIRED_VARS uhid_INCLUDE_DIR uhid_LIBRARIES
  VERSION_VAR uhid_VERSION
  REASON_FAILURE_MESSAGE "Ensure that uhid is installed on the system."
)
mark_as_advanced(uhid_INCLUDE_DIR uhid_LIBRARY)

if(uhid_FOUND)
  if(NOT TARGET uhid::uhid)
    add_library(uhid::uhid MODULE IMPORTED)
    set_property(TARGET uhid::uhid PROPERTY IMPORTED_LOCATION "${uhid_LIBRARIES}")

    set_target_properties(
      uhid::uhid
      PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${uhid_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES "${uhid_LIBRARIES}"
        VERSION ${uhid_VERSION}
    )
  endif()
endif()
