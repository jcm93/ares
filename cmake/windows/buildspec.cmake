include_guard(GLOBAL)

include(buildspec_common)

# _check_dependencies_windows: Set up Windows slice for _check_dependencies
function(_check_dependencies_windows)
  set(dependencies_dir "${CMAKE_CURRENT_SOURCE_DIR}/.deps")
  set(prebuilt_filename "windows-deps-VERSION-ARCH-REVISION.zip")
  set(prebuilt_destination "obs-deps-VERSION-ARCH")

  if(CMAKE_GENERATOR_PLATFORM STREQUAL Win32)
    set(arch x86)
    set(dependencies_list prebuilt)
  else()
    set(arch ${CMAKE_GENERATOR_PLATFORM})
    set(dependencies_list prebuilt qt6 cef)
  endif()
  set(platform windows-${arch})

  _check_dependencies()
endfunction()

_check_dependencies_windows()
