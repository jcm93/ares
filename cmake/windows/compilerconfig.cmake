if(WIN32 AND NOT MINGW)
  add_compile_definitions(EXCLUDE_MANIFEST_FROM_RC) #global
endif()

include_guard(GLOBAL)

include(ccache)
include(compiler_common)

add_compile_definitions(_WIN32_WINNT=0x0601) #global

if(MSVC)
  add_compile_options(
    # none of these are cpp- or c-specific, so just add them wholesale
    /MP
    /Zc:__cplusplus
    /utf-8
    /permissive-
    $<$<NOT:$<CONFIG:Debug>>:/GL>
    $<$<NOT:$<CONFIG:Debug>>:/Oi>
    $<$<NOT:$<CONFIG:Debug>>:/Ob2>
    $<$<NOT:$<CONFIG:Debug>>:/Ot>
  )
  add_link_options(
    $<$<NOT:$<CONFIG:Debug>>:/LTCG>
    $<$<NOT:$<CONFIG:Debug>>:/INCREMENTAL:NO>
    /Debug
  )
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase)
  if(CMAKE_COMPILE_WARNING_AS_ERROR)
    add_link_options(/WX)
  endif()
else()
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:${_ares_clang_c_options}>"
    "$<$<COMPILE_LANGUAGE:CXX>:${_ares_clang_cxx_options}>"
  )
  # any ms-specific clang things?
endif()

if(ARES_BUILD_LOCAL)
  add_compile_options(-march=native)
else()
  # todo
endif()


if(NOT MINGW)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS) #global
endif()
