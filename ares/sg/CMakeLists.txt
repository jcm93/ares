add_core_target(sg)

set(
  sg_PRIMARY_SOURCES
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  ppi/ppi.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  keyboard/keyboard.cpp
)
target_sources(sg PRIVATE ${sg_PRIMARY_SOURCES})

ares_add_components(CORE sg COMPONENT processor/z80 video/tms9918 audio/sn76489 io/i8255)

target_sources(
  sg
  PRIVATE #
    sg.hpp
    CMakeLists.txt
)

target_sources(
  sg
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  sg
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
    cartridge/board/arcade-rom.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/linear.cpp
    cartridge/board/taiwan-a.cpp
    cartridge/board/taiwan-b.cpp
)

target_sources(
  sg
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  sg
  PRIVATE #
    keyboard/keyboard.hpp
)

target_sources(
  sg
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  sg
  PRIVATE #
    ppi/ppi.hpp
    ppi/serialization.cpp
)

target_sources(
  sg
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  sg
  PRIVATE #
    system/arcade-controls.cpp
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  sg
  PRIVATE #
    vdp/color.cpp
    vdp/serialization.cpp
    vdp/vdp.hpp
)

organize_core_sources(CORE sg)
