add_core_target(ngp)

set(
  ngp_PRIMARY_SOURCES
  system/system.cpp
  cartridge/cartridge.cpp
  cpu/cpu.cpp
  apu/apu.cpp
  kge/kge.cpp
  psg/psg.cpp
)
target_sources(ngp PRIVATE ${ngp_PRIMARY_SOURCES})

ares_add_components(CORE ngp COMPONENT processor/tlcs900h processor/z80 audio/t6w28)

target_sources(
  ngp
  PRIVATE #
    ngp.hpp
    CMakeLists.txt
)

target_sources(
  ngp
  PRIVATE #
    apu/apu.hpp
    apu/debugger.cpp
    apu/memory.cpp
    apu/serialization.cpp
)

target_sources(
  ngp
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/debugger.cpp
    cartridge/flash.cpp
    cartridge/flash.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  ngp
  PRIVATE #
    cpu/adc.cpp
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/interrupts.cpp
    cpu/io.cpp
    cpu/memory.cpp
    cpu/ports.cpp
    cpu/rtc.cpp
    cpu/serial.cpp
    cpu/serialization.cpp
    cpu/timers.cpp
    cpu/watchdog.cpp
)

target_sources(
  ngp
  PRIVATE #
    kge/color.cpp
    kge/dac.cpp
    kge/kge.hpp
    kge/memory.cpp
    kge/plane.cpp
    kge/serialization.cpp
    kge/sprite.cpp
    kge/window.cpp
)

target_sources(
  ngp
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  ngp
  PRIVATE #
    system/controls.cpp
    system/debugger.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE ngp)
