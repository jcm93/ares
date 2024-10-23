target_sources(
  ruby
  PRIVATE # cmake-format: sortable
    video/glx.cpp
)

target_sources(
  ruby
  PRIVATE # cmake-format: sortable
    audio/oss.cpp
    audio/alsa.cpp
    audio/openal.cpp
    audio/sdl.cpp
    audio/pulseaudio.cpp
    audio/pulseaudio-simple.cpp
    audio/ao.cpp
)

target_sources(
  ruby
  PRIVATE # cmake-format: sortable
    input/xlib.cpp
    input/sdl.cpp
    input/mouse/xlib.cpp
    input/keyboard/xlib.cpp
    input/joypad/sdl.cpp
    input/joypad/udev.cpp
    input/joypad/uhid.cpp
    input/joypad/xinput.cpp
)

find_package(SDL)
find_package(X11)
find_package(OpenGL)
find_package(OpenAL)
find_package(librashader)
target_link_libraries(ruby PRIVATE X11::Xrandr OpenGL::GLX OpenAL::OpenAL)

if(SDL_FOUND)
  target_enable_feature(ruby "SDL input driver" INPUT_SDL)
  target_enable_feature(ruby "SDL audio driver" AUDIO_SDL)
endif()
if(librashader_FOUND)
  target_enable_feature(ruby "librashader OpenGL runtime" LIBRA_RUNTIME_OPENGL)
endif()

target_compile_definitions(
  ruby
  PRIVATE
  VIDEO_GLX
  AUDIO_OPENAL
)

#elseif(platform STREQUAL linux)
#    pkg_check = $(if $(shell pkg-config $1 && echo 1),$2)
#    list(APPEND ruby video.glx video.glx2 video.xshm)
#    ruby += $(call pkg_check,xv,video.xvideo)
#    list(APPEND ruby audio.oss audio.alsa)
#    ruby += $(call pkg_check,openal,audio.openal)
#    ruby += $(call pkg_check,libpulse,audio.pulseaudio)
#    ruby += $(call pkg_check,libpulse-simple,audio.pulseaudiosimple)
#    ruby += $(call pkg_check,ao,audio.ao)
#    list(APPEND ruby input.xlib)
#    ruby += $(call pkg_check,libudev,input.udev)
#    ruby += $(call pkg_check,sdl2,input.sdl)
#    ruby += $(call pkg_check,sdl2,audio.sdl)
#  elseif(platform STREQUAL bsd)
#    pkg_check = $(if $(shell pkg-config $1 && echo 1),$2)
#    list(APPEND ruby video.glx video.glx2 video.xshm)
#    ruby += $(call pkg_check,xv,video.xvideo)
#    list(APPEND ruby audio.oss)
#    ruby += $(call pkg_check,openal,audio.openal)
#    ruby += $(call pkg_check,libpulse,audio.pulseaudio)
#    ruby += $(call pkg_check,libpulse-simple,audio.pulseaudiosimple)
#    ruby += $(call pkg_check,ao,audio.ao)
#    list(APPEND ruby input.uhid input.xlib)
#    ruby += $(call pkg_check,sdl2,input.sdl)
#    ruby += $(call pkg_check,sdl2,audio.sdl)
#  endif()
#endif()
