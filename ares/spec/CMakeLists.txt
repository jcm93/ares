add_core_target(spec)

set(
  spec_PRIMARY_SOURCES
  keyboard/keyboard.cpp
  expansion/expansion.cpp
  system/system.cpp
  cpu/cpu.cpp
  ula/ula.cpp
  psg/psg.cpp
  tape/tape.cpp
)
target_sources(spec PRIVATE ${spec_PRIMARY_SOURCES})

ares_add_components(CORE spec COMPONENT processor/z80 audio/ay38910)

target_sources(
  spec
  PRIVATE #
    spec.hpp
    CMakeLists.txt
)

target_sources(
  spec
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  spec
  PRIVATE #
    expansion/expansion.hpp
    expansion/port.cpp
    expansion/port.hpp
    expansion/kempston/kempston.cpp
    expansion/kempston/kempston.hpp
)

target_sources(
  spec
  PRIVATE #
    keyboard/keyboard.hpp
)

target_sources(
  spec
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  spec
  PRIVATE #
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  spec
  PRIVATE #
    tape/deck.cpp
    tape/deck.hpp
    tape/tape.hpp
    tape/tray.cpp
    tape/tray.hpp
)

target_sources(
  spec
  PRIVATE #
    ula/color.cpp
    ula/serialization.cpp
    ula/ula.hpp
)

organize_core_sources(CORE spec)
