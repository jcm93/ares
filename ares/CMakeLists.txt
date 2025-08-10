add_library(ares STATIC ares/ares.cpp ares/memory/fixed-allocator.cpp)
add_library(ares::ares ALIAS ares)

configure_file(ares/ares.cpp.in ares/ares.cpp @ONLY)

option(ARES_PROFILE_ACCURACY "Build to prefer emulation accuracy over performance in certain specific areas" OFF)
option(ARES_PRECOMPILE_HEADERS "Precompile ares/ares.hpp header for performance" OFF)
option(
  ARES_UNITY_CORES
  "\
Build each core as one translation unit. Decreases cold build times but increases incremental build times. Slightly \
increases performance.
"
  OFF
)

add_library(ares-headers INTERFACE)
add_library(ares::headers ALIAS ares-headers)
target_include_directories(ares-headers INTERFACE ${CMAKE_SOURCE_DIR}/ares)
target_link_libraries(ares-headers INTERFACE ares::nall::headers)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ares/ares.hpp)
set_target_properties(ares-headers PROPERTIES FOLDER ares PREFIX "")

add_sourcery_command(ares-headers ares/resource)
target_link_libraries(ares-headers INTERFACE libco sljit nall)

if(ARES_PROFILE_ACCURACY)
  target_compile_definitions(ares-headers INTERFACE PROFILE_ACCURACY)
else()
  target_compile_definitions(ares-headers INTERFACE PROFILE_PERFORMANCE)
endif()

target_sources(
  ares
  PRIVATE
    ares/ares.cpp
    ares/ares.cpp.in
    ares/ares.hpp
    ares/inline.hpp
    ares/platform.hpp
    ares/random.hpp
    ares/types.hpp
    component/CMakeLists.txt
)

target_sources(
  ares
  PRIVATE
    ares/debug/debug.cpp
    ares/debug/debug.hpp
    ares/memory/fixed-allocator.cpp
    ares/memory/fixed-allocator.hpp
    ares/memory/memory.hpp
    ares/memory/readable.hpp
    ares/memory/writable.hpp
)

target_sources(
  ares
  PRIVATE #
    ares/resource/resource.cpp
    ares/resource/resource.hpp
)

target_sources(
  ares
  PRIVATE ares/scheduler/scheduler.cpp ares/scheduler/scheduler.hpp ares/scheduler/thread.cpp ares/scheduler/thread.hpp
)

target_sources(
  ares
  PRIVATE
    ares/node/attribute.hpp
    ares/node/class.hpp
    ares/node/node.cpp
    ares/node/node.hpp
    ares/node/object.hpp
    ares/node/peripheral.hpp
    ares/node/port.hpp
    ares/node/system.hpp
)

target_sources(ares PRIVATE ares/node/audio/audio.hpp ares/node/audio/stream.cpp ares/node/audio/stream.hpp)

target_sources(ares PRIVATE ares/node/component/component.hpp ares/node/component/real-time-clock.hpp)

target_sources(
  ares
  PRIVATE
    ares/node/input/axis.hpp
    ares/node/input/button.hpp
    ares/node/input/input.hpp
    ares/node/input/rumble.hpp
    ares/node/input/trigger.hpp
)

target_sources(
  ares
  PRIVATE
    ares/node/setting/boolean.hpp
    ares/node/setting/integer.hpp
    ares/node/setting/natural.hpp
    ares/node/setting/real.hpp
    ares/node/setting/setting.hpp
    ares/node/setting/string.hpp
)

target_sources(
  ares
  PRIVATE
    ares/node/video/screen.cpp
    ares/node/video/screen.hpp
    ares/node/video/sprite.cpp
    ares/node/video/sprite.hpp
    ares/node/video/video.hpp
)

if(OS_WINDOWS)
  include(cmake/os-windows.cmake)
elseif(OS_MACOS)
  include(cmake/os-macos.cmake)
elseif(OS_LINUX OR OS_FREEBSD OR OS_OPENBSD)
  include(cmake/os-linux.cmake)
endif()

macro(ares_add_components)
  set(options "")
  set(oneValueArgs CORE)
  set(multiValueArgs COMPONENT)
  cmake_parse_arguments(ACN "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  list(APPEND ARES_COMPONENTS ${ACN_COMPONENT})
  set(ARES_COMPONENTS ${ARES_COMPONENTS} PARENT_SCOPE)
  foreach(comp IN ITEMS ${ACN_COMPONENT})
    string(REPLACE "/" ";" ACN_COMPONENT_COMPONENTS "${comp}")
    list(GET ACN_COMPONENT_COMPONENTS -1 ACN_COMPONENT_TARGET_NAME)
    target_link_libraries(${ACN_CORE} PUBLIC ${ACN_COMPONENT_TARGET_NAME})
    list(APPEND ARES_COMPONENT_LIBRARIES ${ACN_COMPONENT_TARGET_NAME})
    set(ARES_COMPONENT_LIBRARIES ${ARES_COMPONENT_LIBRARIES} PARENT_SCOPE)
  endforeach()
endmacro()

macro(organize_core_sources)
  set(options "")
  set(oneValueArgs CORE)
  set(multiValueArgs "")
  cmake_parse_arguments(OCS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(ARES_UNITY_CORES)
    target_sources(${OCS_CORE} PRIVATE ${OCS_CORE}.cpp)
  endif()
  get_target_property(${OCS_CORE}_SOURCES ${OCS_CORE} SOURCES)
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${OCS_CORE}_SOURCES})
  set_source_files_properties(${${OCS_CORE}_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
  if(ARES_UNITY_CORES)
    set_source_files_properties(${OCS_CORE} ${OCS_CORE}.cpp PROPERTIES HEADER_FILE_ONLY FALSE)
  else()
    set_source_files_properties(${OCS_CORE} ${${OCS_CORE}_PRIMARY_SOURCES} PROPERTIES HEADER_FILE_ONLY FALSE)
  endif()
  set_target_properties(${OCS_CORE} PROPERTIES FOLDER ares PREFIX "")
endmacro()

list(TRANSFORM ARES_CORES STRIP)

macro(add_core_target core)
  add_library("${core}" OBJECT)
  add_library("ares::${core}" ALIAS ${core})
  set_target_properties("${core}" PROPERTIES OUTPUT_NAME "core-${core}")
  target_link_libraries(${core} PRIVATE ares::headers)
  target_include_directories(${core} PRIVATE ${CMAKE_SOURCE_DIR}/ares)
  if(ARES_PRECOMPILE_HEADERS)
    target_precompile_headers(${core} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:ares/ares.hpp>")
  endif()
endmacro()

if(a26 IN_LIST ARES_CORES)
  enable_core("Atari 2600")
  add_subdirectory(a26)
else()
  disable_core("Atari 2600")
endif()

if(cv IN_LIST ARES_CORES)
  enable_core("ColecoVision")
  add_subdirectory(cv)
else()
  disable_core("ColecoVision")
endif()

if(fc IN_LIST ARES_CORES)
  enable_core("NES / Famicom")
  add_subdirectory(fc)
else()
  disable_core("NES / Famicom")
endif()

if(gb IN_LIST ARES_CORES)
  enable_core("Game Boy / Game Boy Color")
  add_subdirectory(gb)
else()
  disable_core("Game Boy / Game Boy Color")
endif()

if(gba IN_LIST ARES_CORES)
  enable_core("Game Boy Advance")
  add_subdirectory(gba)
else()
  disable_core("Game Boy Advance")
endif()

if(md IN_LIST ARES_CORES)
  enable_core("Sega Mega Drive / Genesis")
  add_subdirectory(md)
else()
  disable_core("Sega Mega Drive / Genesis")
endif()

if(ms IN_LIST ARES_CORES)
  enable_core("Sega Master System / Mark III")
  add_subdirectory(ms)
else()
  disable_core("Sega Master System / Mark III")
endif()

if(msx IN_LIST ARES_CORES)
  enable_core("Microsoft MSX")
  add_subdirectory(msx)
else()
  disable_core("Microsoft MSX")
endif()

if(myvision IN_LIST ARES_CORES)
  enable_core("My Vision")
  add_subdirectory(myvision)
else()
  disable_core("My Vision")
endif()

if(n64 IN_LIST ARES_CORES)
  enable_core("Nintendo 64")
  add_subdirectory(n64)
else()
  disable_core("Nintendo 64")
endif()

if(ng IN_LIST ARES_CORES)
  enable_core("Neo Geo (AES/MVS)")
  add_subdirectory(ng)
else()
  disable_core("Neo Geo (AES/MVS)")
endif()

if(ngp IN_LIST ARES_CORES)
  enable_core("Neo Geo Pocket / Neo Geo Pocket Color")
  add_subdirectory(ngp)
else()
  disable_core("Neo Geo Pocket / Neo Geo Pocket Color")
endif()

if(pce IN_LIST ARES_CORES)
  enable_core("PC-Engine / TurboGrafx")
  add_subdirectory(pce)
else()
  disable_core("PC-Engine / TurboGrafx")
endif()

if(ps1 IN_LIST ARES_CORES)
  enable_core("PlayStation")
  add_subdirectory(ps1)
else()
  disable_core("Playstation")
endif()

if(saturn IN_LIST ARES_CORES)
  enable_core("Sega Saturn")
  add_subdirectory(saturn)
else()
  disable_core("Sega Saturn")
endif()

if(sfc IN_LIST ARES_CORES)
  enable_core("SNES / Super Famicom")
  add_subdirectory(sfc)
else()
  disable_core("SNES / Super Famicom")
endif()

if(sg IN_LIST ARES_CORES)
  enable_core("Sega SG-1000")
  add_subdirectory(sg)
else()
  disable_core("Sega SG-1000")
endif()

if(spec IN_LIST ARES_CORES)
  enable_core("ZX Spectrum")
  add_subdirectory(spec)
else()
  disable_core("ZX Spectrum")
endif()

if(ws IN_LIST ARES_CORES)
  enable_core("WonderSwan / WonderSwan Color")
  add_subdirectory(ws)
else()
  disable_core("WonderSwan / WonderSwan Color")
endif()

foreach(ITEM IN LISTS ARES_CORES)
  list(APPEND ARES_CORES_TARGETS "ares::${ITEM}")
  target_compile_definitions(ares PUBLIC CORE_$<UPPER_CASE:${ITEM}>)
endforeach()

get_target_property(ares_SOURCES ares SOURCES)

set_source_files_properties(
  ares
  ares/debug/debug.cpp
  ares/node/audio/stream.cpp
  ares/node/node.cpp
  ares/node/video/screen.cpp
  ares/node/video/sprite.cpp
  ares/scheduler/thread.cpp
  ares/scheduler/scheduler.cpp
  ares/resource/resource.cpp
  PROPERTIES HEADER_FILE_ONLY TRUE
)

target_sources(ares PRIVATE cmake/os-macos.cmake cmake/os-windows.cmake cmake/os-linux.cmake)

set_source_files_properties(ares ${ARES_HEADER_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_source_files_properties(ares ares/ares.cpp ares/memory/fixed-allocator.cpp PROPERTIES HEADER_FILE_ONLY FALSE)

target_include_directories(ares INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ares_SOURCES})

add_subdirectory(component)

list(REMOVE_DUPLICATES ARES_COMPONENT_LIBRARIES)

target_link_libraries(ares PRIVATE ares::headers ${ARES_CORES_TARGETS} ${ARES_COMPONENT_LIBRARIES})
