if(WIN32 AND NOT MINGW)
  add_compile_definitions(EXCLUDE_MANIFEST_FROM_RC) #global
endif()

if(arch STREQUAL x86 OR arch STREQUAL amd64)
  if(NOT MSVC)
    if(local)
      add_compile_options(-march=native) #global
    else()
      # For official builds, default to x86-64-v2 (Intel Nehalem, AMD Bulldozer) which supports up to SSE 4.2.
      add_compile_options(-march=x86-64-v2) #global
    endif()
  endif()
endif()

# windows settings
if(OS_WINDOWS)
  # target Windows 7
  add_compile_definitions(_WIN32_WINNT=0x0601) #global
  if(NOT MINGW)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS) #global
  endif()
endif()
