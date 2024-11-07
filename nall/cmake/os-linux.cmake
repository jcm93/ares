target_compile_definitions(nall PUBLIC PLATFORM_LINUX)

target_sources(
  nall
  PRIVATE # cmake-format: sortable
    xorg/clipboard.hpp
    xorg/guard.hpp
    xorg/xorg.hpp
)

if(DEFINED ARES_PREFIX)

  target_compile_definitions(nall PRIVATE "ARES_PREFIX=${ARES_PREFIX}")
  
  install(CODE "
    if(NOT \"${CMAKE_INSTALL_PREFIX}\" STREQUAL \"${ARES_PREFIX}\")
      message(FATAL_ERROR \" nall was configured and built with the data directory prefix ${ARES_PREFIX}, but the chosen CMake install prefix, ${CMAKE_INSTALL_PREFIX}, does not match. This is considered an error because it makes it unlikely for the program to properly locate shared resources in the shared data directory.\")
    endif()
  ")
  
endif()
