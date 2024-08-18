add_executable(desktop-ui
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

target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          desktop-ui.hpp
          game-browser/game-browser.hpp
          input/hotkeys.cpp
          input/input.hpp
          presentation/presentation.hpp)
          
target_sources(
  desktop-ui
  PRIVATE game-browser/game-browser.hpp)
  
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          input/hotkeys.cpp
          input/input.hpp)
          
target_sources(
  desktop-ui
  PRIVATE presentation/presentation.hpp)
  
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          program/drivers.cpp
          program/load.cpp
          program/platform.cpp
          program/program.hpp
          program/rewind.cpp
          program/states.cpp
          program/utility.cpp)
          
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          resource/resource.cpp
          resource/resource.hpp)
          
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          settings/audio.cpp
          settings/debug.cpp
          settings/drivers.cpp
          settings/emulators.cpp
          settings/firmware.cpp
          settings/home.cpp
          settings/hotkeys.cpp
          settings/input.cpp
          settings/options.cpp
          settings/paths.cpp
          settings/settings.hpp
          settings/video.cpp)
          
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          tools/cheats.cpp
          tools/graphics.cpp
          tools/manifest.cpp
          tools/memory.cpp
          tools/properties.cpp
          tools/streams.cpp
          tools/tools.hpp
          tools/tracer.cpp)
          
target_sources(
  desktop-ui
  PRIVATE # cmake-format: sortable
          emulator/arcade.cpp
          emulator/atari-2600.cpp
          emulator/colecovision.cpp
          emulator/emulator.cpp
          emulator/emulator.hpp
          emulator/emulators.cpp
          emulator/famicom-disk-system.cpp
          emulator/famicom.cpp
          emulator/game-boy-advance.cpp
          emulator/game-boy-color.cpp
          emulator/game-boy.cpp
          emulator/game-gear.cpp
          emulator/master-system.cpp
          emulator/mega-32x.cpp
          emulator/mega-cd-32x.cpp
          emulator/mega-cd.cpp
          emulator/mega-drive.cpp
          emulator/msx.cpp
          emulator/msx2.cpp
          emulator/myvision.cpp
          emulator/neo-geo-aes.cpp
          emulator/neo-geo-mvs.cpp
          emulator/neo-geo-pocket-color.cpp
          emulator/neo-geo-pocket.cpp
          emulator/nintendo-64.cpp
          emulator/nintendo-64dd.cpp
          emulator/pc-engine-cd.cpp
          emulator/pc-engine.cpp
          emulator/playstation.cpp
          emulator/pocket-challenge-v2.cpp
          emulator/saturn.cpp
          emulator/sg-1000.cpp
          emulator/super-famicom.cpp
          emulator/supergrafx-cd.cpp
          emulator/supergrafx.cpp
          emulator/wonderswan-color.cpp
          emulator/wonderswan.cpp
          emulator/zx-spectrum-128.cpp
          emulator/zx-spectrum.cpp)
          
get_target_property(desktop-ui_SOURCES desktop-ui SOURCES)
          
set_source_files_properties(
  desktop-ui
  ${desktop-ui_SOURCES}
  PROPERTIES
  HEADER_FILE_ONLY
  TRUE)
  
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
  PROPERTIES
  HEADER_FILE_ONLY
  FALSE)

target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty)
target_include_directories(desktop-ui PRIVATE ${CMAKE_SOURCE_DIR}/ares)

if(PLATFORM_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX)
  include(cmake/os-linux.cmake)
elseif(OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-freebsd.cmake)
endif()

target_link_libraries(desktop-ui PRIVATE ares::nall ares::ruby ares::hiro ares::ares ares::mia chdr-static)

set_target_properties(
  desktop-ui
  PROPERTIES
  OUTPUT_NAME ares
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${desktop-ui_SOURCES})

add_sourcery_command(desktop-ui resource)

if(WIN32)
  target_sources(desktop-ui PRIVATE
    resource/ares.rc
    resource/ares.Manifest
  )
endif()

set_target_properties_ares(desktop-ui)
