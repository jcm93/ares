add_core_target(gba)

set(
  gba_PRIMARY_SOURCES
  memory/memory.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  player/player.cpp
  cpu/cpu.cpp
  display/display.cpp
  ppu/ppu.cpp
  apu/apu.cpp
)

target_sources(gba PRIVATE ${gba_PRIMARY_SOURCES})

ares_add_components(CORE gba COMPONENT processor/arm7tdmi rtc/s3511a)

target_sources(
  gba
  PRIVATE #
)

target_sources(
  gba
  PRIVATE #
    gba.hpp
    CMakeLists.txt
)

target_sources(
  gba
  PRIVATE #
    apu/apu.hpp
    apu/fifo.cpp
    apu/io.cpp
    apu/noise.cpp
    apu/sequencer.cpp
    apu/serialization.cpp
    apu/square.cpp
    apu/square1.cpp
    apu/square2.cpp
    apu/wave.cpp
)

target_sources(
  gba
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/eeprom.cpp
    cartridge/flash.cpp
    cartridge/gpio.cpp
    cartridge/memory.hpp
    cartridge/mrom.cpp
    cartridge/rtc.cpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
    cartridge/sram.cpp
)

target_sources(
  gba
  PRIVATE #
    cpu/bus.cpp
    cpu/coprocessor.cpp
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/dma.cpp
    cpu/io.cpp
    cpu/keypad.cpp
    cpu/memory.cpp
    cpu/prefetch.cpp
    cpu/serialization.cpp
    cpu/timer.cpp
)

target_sources(
  gba
  PRIVATE #
    display/display.hpp
    display/io.cpp
    display/serialization.cpp
)

target_sources(
  gba
  PRIVATE #
    memory/memory.hpp
)

target_sources(
  gba
  PRIVATE #
    player/player.hpp
    player/serialization.cpp
)

target_sources(
  gba
  PRIVATE #
    ppu/background.cpp
    ppu/color.cpp
    ppu/dac.cpp
    ppu/debugger.cpp
    ppu/io.cpp
    ppu/memory.cpp
    ppu/object.cpp
    ppu/ppu.hpp
    ppu/serialization.cpp
    ppu/window.cpp
)

target_sources(
  gba
  PRIVATE #
    system/bios.cpp
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE gba)
