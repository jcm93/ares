add_executable(
  desktop-ui
  desktop-ui.cpp
  resource/resource.cpp
  input/input.cpp
  emulator/emulator.cpp
  game-browser/game-browser.cpp
  program/program.cpp
  presentation/presentation.cpp
  settings/settings.cpp
  tools/tools.cpp
)

include(cmake/sources.cmake)

get_target_property(desktop-ui_SOURCES desktop-ui SOURCES)

set_source_files_properties(desktop-ui ${desktop-ui_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_source_files_properties(
  desktop-ui
  desktop-ui.cpp
  resource/resource.cpp
  input/input.cpp
  emulator/emulator.cpp
  game-browser/game-browser.cpp
  program/program.cpp
  presentation/presentation.cpp
  settings/settings.cpp
  tools/tools.cpp
  PROPERTIES HEADER_FILE_ONLY FALSE
)

target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty)
target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR}/ares)

if(OS_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX)
  include(cmake/os-linux.cmake)
elseif(OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-freebsd.cmake)
endif()

target_link_libraries(
  desktop-ui
  PRIVATE nall ares::ruby ares::hiro ares::ares mia chdr-static
)

set_target_properties(desktop-ui PROPERTIES OUTPUT_NAME ares)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${desktop-ui_SOURCES})

add_sourcery_command(desktop-ui resource)

ares_configure_executable(desktop-ui)
