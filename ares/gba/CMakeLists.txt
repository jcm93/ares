ares_components(
  arm7tdmi
)

target_sources(ares PRIVATE
  memory/memory.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  player/player.cpp
  cpu/cpu.cpp
  ppu/ppu.cpp
  apu/apu.cpp
)

ares_add_header_sources(gba
  # cmake-format: sortable
  gba.hpp CMakeLists.txt)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  apu/apu.hpp
  apu/fifo.cpp
  apu/io.cpp
  apu/noise.cpp
  apu/sequencer.cpp
  apu/serialization.cpp
  apu/square.cpp
  apu/square1.cpp
  apu/square2.cpp
  apu/wave.cpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  cartridge/cartridge.hpp
  cartridge/eeprom.cpp
  cartridge/flash.cpp
  cartridge/memory.hpp
  cartridge/mrom.cpp
  cartridge/serialization.cpp
  cartridge/slot.cpp
  cartridge/slot.hpp
  cartridge/sram.cpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  cpu/bus.cpp
  cpu/cpu.hpp
  cpu/debugger.cpp
  cpu/dma.cpp
  cpu/io.cpp
  cpu/keypad.cpp
  cpu/memory.cpp
  cpu/prefetch.cpp
  cpu/serialization.cpp
  cpu/timer.cpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  memory/memory.hpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  player/player.hpp
  player/serialization.cpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  ppu/background.cpp
  ppu/color.cpp
  ppu/dac.cpp
  ppu/debugger.cpp
  ppu/io.cpp
  ppu/memory.cpp
  ppu/object.cpp
  ppu/ppu.hpp
  ppu/serialization.cpp
  ppu/window.cpp)
  
ares_add_header_sources(gba
  # cmake-format: sortable
  system/bios.cpp
  system/controls.cpp
  system/serialization.cpp
  system/system.hpp)
