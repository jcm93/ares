ares_components(
  v30mz
  m93lcx6
)

target_sources(ares PRIVATE
  system/system.cpp
  memory/memory.cpp
  eeprom/eeprom.cpp
  cartridge/cartridge.cpp
  cpu/cpu.cpp
  ppu/ppu.cpp
  apu/apu.cpp
  serial/serial.cpp
)

ares_add_header_sources(ws ws.hpp CMakeLists.txt)

ares_add_header_sources(ws
  # cmake-format: sortable
  apu/apu.hpp
  apu/channel1.cpp
  apu/channel2.cpp
  apu/channel3.cpp
  apu/channel4.cpp
  apu/channel5.cpp
  apu/debugger.cpp
  apu/dma.cpp
  apu/io.cpp
  apu/serialization.cpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  cartridge/cartridge.hpp
  cartridge/debugger.cpp
  cartridge/flash.cpp
  cartridge/io.cpp
  cartridge/karnak.cpp
  cartridge/memory.cpp
  cartridge/rtc.cpp
  cartridge/serialization.cpp
  cartridge/slot.cpp
  cartridge/slot.hpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  cpu/cpu.hpp
  cpu/debugger.cpp
  cpu/dma.cpp
  cpu/interrupt.cpp
  cpu/io.cpp
  cpu/keypad.cpp
  cpu/serialization.cpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  eeprom/eeprom.hpp
  eeprom/serialization.cpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  memory/memory.hpp)

ares_add_header_sources(ws
  # cmake-format: sortable
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
  ppu/window.cpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  serial/debugger.cpp
  serial/serial.hpp
  serial/serialization.cpp)

ares_add_header_sources(ws
  # cmake-format: sortable
  system/controls.cpp
  system/debugger.cpp
  system/io.cpp
  system/serialization.cpp
  system/system.hpp)
