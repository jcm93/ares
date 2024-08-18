add_library(nall OBJECT main.cpp nall.cpp sljitAllocator.cpp)
add_library(ares::nall ALIAS nall)

include(cmake/sources.cmake)
          
set_source_files_properties(
  nall
  memory.cpp
  thread.cpp
  tcptext/tcp-socket.cpp
  tcptext/tcptext-server.cpp
  gdb/server.cpp
  directory.cpp
  dl.cpp
  file-map.cpp
  inode.cpp
  path.cpp
  platform.cpp
  random.cpp
  run.cpp
  terminal.cpp
  PROPERTIES
  HEADER_FILE_ONLY
  TRUE)
  
set_source_files_properties(
  nall
  nall.cpp
  PROPERTIES
  HEADER_FILE_ONLY
  FALSE)

target_link_libraries(nall PUBLIC sljit chdr-static)

if(PLATFORM_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX)
  include(cmake/os-linux.cmake)
elseif(OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-freebsd.cmake)
endif()

get_target_property(nall_SOURCES nall SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${nall_SOURCES})

# global compiler flags
target_compile_features(nall PUBLIC c_std_11)
set_target_properties(nall PROPERTIES C_EXTENSIONS OFF)

target_compile_features(nall PUBLIC cxx_std_17)
set_target_properties(nall PROPERTIES CXX_EXTENSIONS OFF)

target_compile_definitions(nall PUBLIC BUILD_$<UPPER_CASE:${build}>)

if(local)
  target_compile_definitions(nall PUBLIC BUILD_LOCAL)
endif()

target_include_directories(nall PRIVATE ${CMAKE_SOURCE_DIR})
