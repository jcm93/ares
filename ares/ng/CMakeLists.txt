add_core_target(ng)

set(
  ng_PRIMARY_SOURCES
  system/system.cpp
  cpu/cpu.cpp
  apu/apu.cpp
  lspc/lspc.cpp
  opnb/opnb.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  card/card.cpp
)
target_sources(ng PRIVATE ${ng_PRIMARY_SOURCES})

ares_add_components(CORE ng COMPONENT processor/m68000 processor/z80)

target_link_libraries(ng PRIVATE ymfm)

target_sources(
  ng
  PRIVATE #
    ng.hpp
    CMakeLists.txt
)

target_sources(
  ng
  PRIVATE #
    apu/apu.hpp
    apu/debugger.cpp
    apu/memory.cpp
    apu/serialization.cpp
)

target_sources(
  ng
  PRIVATE #
    card/card.hpp
    card/debugger.cpp
    card/serialization.cpp
    card/slot.cpp
    card/slot.hpp
)

target_sources(
  ng
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/jockey-gp.cpp
    cartridge/board/mslugx.cpp
    cartridge/board/rom.cpp
)

target_sources(
  ng
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  ng
  PRIVATE #
    controller/arcade-stick/arcade-stick.cpp
    controller/arcade-stick/arcade-stick.hpp
)

target_sources(
  ng
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  ng
  PRIVATE #
    lspc/color.cpp
    lspc/debugger.cpp
    lspc/lspc.hpp
    lspc/render.cpp
    lspc/serialization.cpp
)

target_sources(
  ng
  PRIVATE #
    opnb/opnb.hpp
    opnb/serialization.cpp
)

target_sources(
  ng
  PRIVATE #
    system/debugger.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE ng)
