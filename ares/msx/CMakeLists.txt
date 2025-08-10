add_core_target(msx)

set(
  msx_PRIMARY_SOURCES
  system/system.cpp
  keyboard/keyboard.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  tape/tape.cpp
  rtc/rtc.cpp
)
target_sources(msx PRIVATE ${msx_PRIMARY_SOURCES})

ares_add_components(
  CORE msx
  COMPONENT processor/z80 video/tms9918 video/v9938 audio/ay38910 audio/ym2413
)

target_sources(
  msx
  PRIVATE #
)

target_sources(
  msx
  PRIVATE #
    msx.hpp
    CMakeLists.txt
)

target_sources(
  msx
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  msx
  PRIVATE #
    cartridge/board/asc16.cpp
    cartridge/board/asc8.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/cross-blaim.cpp
    cartridge/board/konami-scc.cpp
    cartridge/board/konami.cpp
    cartridge/board/linear.cpp
    cartridge/board/mirrored.cpp
    cartridge/board/super-lode-runner.cpp
    cartridge/board/super-pierrot.cpp
)

target_sources(
  msx
  PRIVATE #
    controller/controller.hpp
    controller/mux.cpp
    controller/mux.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  msx
  PRIVATE #
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  msx
  PRIVATE #
    controller/vaus-paddle/vaus-paddle.cpp
    controller/vaus-paddle/vaus-paddle.hpp
)

target_sources(
  msx
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  msx
  PRIVATE #
    keyboard/keyboard.hpp
    keyboard/serialization.cpp
)

target_sources(
  msx
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  msx
  PRIVATE #
    rtc/rtc.hpp
    rtc/serialization.cpp
)

target_sources(
  msx
  PRIVATE #
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  msx
  PRIVATE #
    tape/deck.cpp
    tape/deck.hpp
    tape/tape.hpp
    tape/tray.cpp
    tape/tray.hpp
)

target_sources(
  msx
  PRIVATE #
    vdp/color.cpp
    vdp/serialization.cpp
    vdp/vdp.hpp
)

organize_core_sources(CORE msx)
