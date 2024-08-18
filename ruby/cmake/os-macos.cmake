find_package(SDL)
find_package(librashader)

target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          video/cgl.cpp
          video/metal/metal.cpp
          video/metal/metal.hpp
          video/metal/Shaders.metal
          video/metal/ShaderTypes.h)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          audio/openal.cpp
          audio/sdl.cpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          input/quartz.cpp
          input/keyboard/quartz.cpp
          input/sdl.cpp
          input/mouse/nsmouse.cpp
          input/joypad/iokit.cpp
          input/joypad/sdl.cpp)
          
target_sources(
  ruby
  PRIVATE cmake/os-macos.cmake)
  
# Explicitly mark ruby.cpp as Objective-C++
set_source_files_properties(
  ruby
  ruby.cpp
  PROPERTIES
  XCODE_EXPLICIT_FILE_TYPE
  sourcecode.cpp.objcpp)
  
target_link_libraries(
  ruby
  PRIVATE # cmake-format: sortable
          "$<LINK_LIBRARY:FRAMEWORK,CoreAudio.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,IOKit.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,QuartzCore.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,OpenAL.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,OpenGL.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,Metal.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,MetalKit.framework>"
          $<$<BOOL:${SDL_FOUND}>:SDL::SDL>
          $<$<BOOL:${librashader_FOUND}>:librashader::librashader>)


target_enable_feature(ruby "OpenGL video driver" VIDEO_CGL)
target_enable_feature(ruby "Metal video driver" VIDEO_METAL)
target_enable_feature(ruby "OpenAL audio driver" AUDIO_OPENAL)
if(SDL_FOUND)
  target_enable_feature(ruby "SDL input driver" INPUT_SDL)
  target_enable_feature(ruby "SDL audio driver" AUDIO_SDL)
endif()
if(librashader_FOUND)
  target_enable_feature(ruby "librashader OpenGL runtime" LIBRA_RUNTIME_OPENGL)
  target_enable_feature(ruby "librashader Metal runtime" LIBRA_RUNTIME_METAL)
endif()
target_enable_feature(ruby "Quartz input driver" INPUT_QUARTZ)

target_compile_definitions(ruby PUBLIC PLATFORM_MACOS)
          
set_target_properties_ares(ruby)


