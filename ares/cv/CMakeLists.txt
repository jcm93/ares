add_core_target(cv)

set(
  cv_PRIMARY_SOURCES
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
)
target_sources(cv PRIVATE ${cv_PRIMARY_SOURCES})

ares_add_components(CORE cv COMPONENT processor/z80 video/tms9918 audio/sn76489)

target_sources(
  cv
  PRIVATE #
    cv.hpp
    CMakeLists.txt
)

target_sources(
  cv
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  cv
  PRIVATE #
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/coleco.cpp
    cartridge/board/megacart.cpp
    cartridge/board/xin1.cpp
)

target_sources(
  cv
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  cv
  PRIVATE #
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  cv
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  cv
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  cv
  PRIVATE #
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  cv
  PRIVATE #
    vdp/color.cpp
    vdp/serialization.cpp
    vdp/vdp.hpp
)

organize_core_sources(CORE cv)
