add_core_target(myvision)

set(
  myvision_PRIMARY_SOURCES
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  system/system.cpp
  cartridge/cartridge.cpp
)
target_sources(myvision PRIVATE ${myvision_PRIMARY_SOURCES})

ares_add_components(CORE myvision COMPONENT processor/z80 video/tms9918 audio/ay38910)

target_sources(
  myvision
  PRIVATE #
)

target_sources(
  myvision
  PRIVATE #
    myvision.hpp
    CMakeLists.txt
)

target_sources(
  myvision
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  myvision
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  myvision
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  myvision
  PRIVATE #
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  myvision
  PRIVATE #
    vdp/color.cpp
    vdp/serialization.cpp
    vdp/vdp.hpp
)

organize_core_sources(CORE myvision)
