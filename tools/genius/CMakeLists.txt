add_executable(genius genius.cpp)

target_sources(genius PRIVATE genius.hpp)

target_include_directories(genius PRIVATE ${CMAKE_SOURCE_DIR})

if(PLATFORM_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX)
  include(cmake/os-linux.cmake)
elseif(OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-freebsd.cmake)
endif()

target_link_libraries(genius PRIVATE nall ares::hiro)

set_target_properties_ares(genius)
