target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          video/direct3d9.cpp
          video/wgl.cpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          audio/wasapi.cpp
          audio/xaudio2.cpp
          audio/xaudio2.hpp
          audio/directsound.cpp
          audio/waveout.cpp
          audio/sdl.cpp)
          
target_sources(
  ruby
  PRIVATE # cmake-format: sortable
          input/sdl.cpp
          input/shared/rawinput.cpp
          input/windows.cpp
          input/keyboard/rawinput.cpp
          input/mouse/rawinput.cpp
          input/joypad/directinput.cpp)
          
target_compile_definitions(ruby
          VIDEO_DIRECT3D9
          VIDEO_GDI
          VIDEO_WGL
          AUDIO_WASAPI
          AUDIO_XAUDIO2
          AUDIO_DIRECTSOUND
          AUDIO_WAVEOUT
          INPUT_WINDOWS)
          
target_link_libraries(
  ruby
  PRIVATE openal32
          direct3d9
          opengl32
          dsound
          uuid
          avrt
          winmm
          ole32
          dinput8
          dxguid)
          
# if sdl add SDL
find_package(SDL)
