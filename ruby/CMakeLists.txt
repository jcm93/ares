add_library(ruby STATIC)
add_library(ares::ruby ALIAS ruby)

target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          ruby.cpp
          ruby.hpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          audio/audio.cpp
          audio/audio.hpp
          audio/sdl.cpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          input/input.cpp
          input/input.hpp
          input/sdl.cpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          video/video.cpp
          video/video.hpp
          video/opengl/bind.hpp
          video/opengl/main.hpp
          video/opengl/opengl.hpp
          video/opengl/surface.hpp
          video/opengl/texture.hpp
          video/opengl/utility.hpp)
          
          

target_link_libraries(ruby PUBLIC nall PRIVATE thirdparty)

if(PLATFORM_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX)
  include(cmake/os-linux.cmake)
elseif(OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-freebsd.cmake)
endif()

target_include_directories(ruby PRIVATE ${CMAKE_SOURCE_DIR})

get_target_property(ruby_SOURCES ruby SOURCES)

set_source_files_properties(
  ruby
  ${ruby_SOURCES}
  PROPERTIES
  HEADER_FILE_ONLY
  TRUE)
  
set_source_files_properties(
  ruby
  ruby.cpp
  PROPERTIES
  HEADER_FILE_ONLY
  FALSE)
  
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ruby_SOURCES})
