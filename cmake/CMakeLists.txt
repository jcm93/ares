# dummy cmake target used to enable editing of CMake files within generated IDE projects

add_library(cmake INTERFACE)

target_sources(
  cmake
  PRIVATE # cmake-format: sortable
          common/bootstrap.cmake
          common/buildnumber.cmake
          common/buildspec_common.cmake
          common/ccache.cmake
          common/compiler_common.cmake
          common/helpers_common.cmake
          common/osconfig.cmake
          common/versionconfig.cmake
          finders/Findlibrashader.cmake
          finders/FindMoltenVK.cmake
          finders/FindSDL.cmake
          macos/buildspec.cmake
          macos/compilerconfig.cmake
          macos/defaults.cmake
          macos/helpers.cmake
          macos/xcode.cmake
          windows/compilerconfig.cmake
          windows/defaults.cmake
          windows/buildspec.cmake
          windows/helpers.cmake)
          
get_target_property(cmake_SOURCES cmake SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${cmake_SOURCES})
