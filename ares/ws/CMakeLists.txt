add_core_target(ws)

set(
  ws_PRIMARY_SOURCES
  system/system.cpp
  memory/memory.cpp
  eeprom/eeprom.cpp
  cartridge/cartridge.cpp
  cpu/cpu.cpp
  ppu/ppu.cpp
  apu/apu.cpp
  serial/serial.cpp
)
target_sources(ws PRIVATE ${ws_PRIMARY_SOURCES})

ares_add_components(CORE ws COMPONENT processor/v30mz eeprom/m93lcx6)

target_sources(
  ws
  PRIVATE #
    ws.hpp
    CMakeLists.txt
)

target_sources(
  ws
  PRIVATE #
    apu/apu.hpp
    apu/channel1.cpp
    apu/channel2.cpp
    apu/channel3.cpp
    apu/channel4.cpp
    apu/channel5.cpp
    apu/debugger.cpp
    apu/dma.cpp
    apu/io.cpp
    apu/serialization.cpp
)

target_sources(
  ws
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/debugger.cpp
    cartridge/flash.cpp
    cartridge/io.cpp
    cartridge/karnak.cpp
    cartridge/memory.cpp
    cartridge/rtc.cpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  ws
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/dma.cpp
    cpu/interrupt.cpp
    cpu/io.cpp
    cpu/keypad.cpp
    cpu/serialization.cpp
)

target_sources(
  ws
  PRIVATE #
    eeprom/eeprom.hpp
    eeprom/serialization.cpp
)

target_sources(
  ws
  PRIVATE #
    memory/memory.hpp
)

target_sources(
  ws
  PRIVATE #
    ppu/color.cpp
    ppu/dac.cpp
    ppu/debugger.cpp
    ppu/io.cpp
    ppu/memory.cpp
    ppu/ppu.hpp
    ppu/screen.cpp
    ppu/serialization.cpp
    ppu/sprite.cpp
    ppu/timer.cpp
    ppu/window.cpp
)

target_sources(
  ws
  PRIVATE #
    serial/debugger.cpp
    serial/serial.hpp
    serial/serialization.cpp
)

target_sources(
  ws
  PRIVATE #
    system/controls.cpp
    system/debugger.cpp
    system/io.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE ws)
