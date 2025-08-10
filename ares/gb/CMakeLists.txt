add_core_target(gb)

set(
  gb_PRIMARY_SOURCES
  system/system.cpp
  cartridge/cartridge.cpp
  bus/bus.cpp
  cpu/cpu.cpp
  ppu/ppu.cpp
  apu/apu.cpp
)
target_sources(gb PRIVATE ${gb_PRIMARY_SOURCES})

ares_add_components(CORE gb COMPONENT processor/sm83 eeprom/m93lcx6)

target_sources(
  gb
  PRIVATE #
)

target_sources(
  gb
  PRIVATE #
    gb.hpp
    CMakeLists.txt
)

target_sources(
  gb
  PRIVATE #
    apu/apu.hpp
    apu/io.cpp
    apu/noise.cpp
    apu/sequencer.cpp
    apu/serialization.cpp
    apu/square1.cpp
    apu/square2.cpp
    apu/wave.cpp
)

target_sources(
  gb
  PRIVATE #
    bus/bus.hpp
)

target_sources(
  gb
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/memory.cpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  gb
  PRIVATE #
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/huc1.cpp
    cartridge/board/huc3.cpp
    cartridge/board/linear.cpp
    cartridge/board/mbc1.cpp
    cartridge/board/mbc1m.cpp
    cartridge/board/mbc2.cpp
    cartridge/board/mbc3.cpp
    cartridge/board/mbc5.cpp
    cartridge/board/mbc6.cpp
    cartridge/board/mbc7.cpp
    cartridge/board/mmm01.cpp
    cartridge/board/none.cpp
    cartridge/board/tama.cpp
)

target_sources(
  gb
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/io.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
    cpu/timing.cpp
)

target_sources(
  gb
  PRIVATE #
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE gb)
