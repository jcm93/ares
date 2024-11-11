if(WIN32 AND NOT MINGW)
  add_compile_definitions(EXCLUDE_MANIFEST_FROM_RC) #global
endif()

include_guard(GLOBAL)

include(ccache)
include(compiler_common)

if(ENABLE_CCACHE AND CCACHE_PROGRAM)
  if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    file(COPY_FILE ${CCACHE_PROGRAM} "${CMAKE_CURRENT_BINARY_DIR}/cl.exe")
    set(
      CMAKE_VS_GLOBALS
      "CLToolExe=cl.exe"
      "CLToolPath=${CMAKE_BINARY_DIR}"
      "UseMultiToolTask=true"
    )
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
  elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    file(COPY_FILE ${CCACHE_PROGRAM} "${CMAKE_CURRENT_BINARY_DIR}/clang-cl.exe")
    set(
      CMAKE_VS_GLOBALS
      "CLToolExe=clang-cl.exe"
      "CLToolPath=${CMAKE_BINARY_DIR}"
      "UseMultiToolTask=true"
    )
  endif()
endif()

if(CMAKE_GENERATOR_PLATFORM)
  message(AUTHOR_WARNING "cmake generator platform is set to ${CMAKE_GENERATOR_PLATFORM}")
  set(arch ${CMAKE_GENERATOR_PLATFORM})
  set(platform windows-${arch})
else()
  message(AUTHOR_WARNING "cmake system processor is set to ${CMAKE_SYSTEM_PROCESSOR}")
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL ARM64)
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
  /W2
  /MP
  /Zc:__cplusplus
  /utf-8
  /permissive-
  $<$<NOT:$<CONFIG:Debug>>:/GL>
  $<$<NOT:$<CONFIG:Debug>>:/Oi>
  $<$<NOT:$<CONFIG:Debug>>:/Ob2>
  $<$<NOT:$<CONFIG:Debug>>:/Ot>
)

# add compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # we are on either msys2/mingw clang, or clang-cl
  # add common options
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:${_ares_clang_c_options}>"
    "$<$<COMPILE_LANGUAGE:CXX>:${_ares_clang_cxx_options}>"
    "$<$<COMPILE_LANGUAGE:C,CXX>:-Wno-reorder-ctor>"
    "$<$<COMPILE_LANGUAGE:C,CXX>:-Wno-unused>"
  )
  if(NOT MSVC)
    # statically link libstdc++ if compiling under msys2/mingw
    add_link_options(-static-libstdc++)
    # msys2/mingw-specific invocations to make clang emit debug symbols
    set(
      _ares_mingw_clang_debug_compile_options
      -g
      -gcodeview
    )
    set(
      _ares_mingw_clang_debug_link_options
      -fuse-ld=lld
      -g
      -Wl,--pdb=
    )
    add_compile_options("$<$<CONFIG:Debug,RelWithDebInfo>:${_ares_mingw_clang_debug_compile_options}>")
    add_link_options("$<$<CONFIG:Debug,RelWithDebInfo>:${_ares_mingw_clang_debug_link_options}>")
  else()
    # generate PDBs rather than embed debug symbols
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase)
  endif()
  
  # optimizations
  if(ARES_BUILD_LOCAL)
    add_compile_options(-march=native)
  else()
    if(${arch} STREQUAL x64)
      add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:-march=x86-64-v2>")
    endif()
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:C,CXX>:${_ares_msvc_cxx_options}>"
  )
  # should be covered by CMAKE_INTERPROCEDURAL_OPTIMIZATION
#   add_link_options(
#     $<$<NOT:$<CONFIG:Debug>>:/LTCG>
#     $<$<NOT:$<CONFIG:Debug>>:/INCREMENTAL:NO>
#     /Debug
#   )
  if(CMAKE_COMPILE_WARNING_AS_ERROR)
    add_link_options(/WX)
  endif()
endif()


if(NOT MINGW)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS) #global
endif()
