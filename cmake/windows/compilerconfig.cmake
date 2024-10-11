if(WIN32 AND NOT MINGW)
  add_compile_definitions(EXCLUDE_MANIFEST_FROM_RC) #global
endif()

include_guard(GLOBAL)

include(ccache)
include(compiler_common)

if(CMAKE_GENERATOR_PLATFORM)
  set(arch ${CMAKE_GENERATOR_PLATFORM})
  set(platform windows-${arch})
else()
  if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL ARM64)
    set(arch arm64)
    set(platform windows-${arch})
  else()
    set(arch x64)
    set(platform windows-${arch})
  endif()
endif()

add_compile_definitions(_WIN32_WINNT=0x0601) #global

set(
  _ares_msvc_cxx_options
  /MP
  /Zc:__cplusplus
  /utf-8
  /permissive-
  $<$<NOT:$<CONFIG:Debug>>:/GL>
  $<$<NOT:$<CONFIG:Debug>>:/Oi>
  $<$<NOT:$<CONFIG:Debug>>:/Ob2>
  $<$<NOT:$<CONFIG:Debug>>:/Ot>
)

if(MSVC)
  if(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options(
      "$<$<COMPILE_LANGUAGE:C,CXX>:${_ares_msvc_cxx_options}>"
    )
    add_link_options(
      $<$<NOT:$<CONFIG:Debug>>:/LTCG>
      $<$<NOT:$<CONFIG:Debug>>:/INCREMENTAL:NO>
      /Debug
    )
    if(CMAKE_COMPILE_WARNING_AS_ERROR)
      add_link_options(/WX)
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options(
      "$<$<COMPILE_LANGUAGE:C>:${_ares_clang_c_options}>"
      "$<$<COMPILE_LANGUAGE:CXX>:${_ares_clang_cxx_options}>"
    )
    -Wno-reorder-ctor
    -Wno-unused
  endif()
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase)
else()
  # msys2
endif()

if(ARES_BUILD_LOCAL)
  if(NOT MSVC)
    add_compile_options(-march=native)
  endif()
else()
  # todo
endif()


if(NOT MINGW)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS) #global
endif()
