add_core_target(a26)

set(
  a26_PRIMARY_SOURCES
  system/system.cpp
  controller/controller.cpp
  cartridge/cartridge.cpp
  cpu/cpu.cpp
  tia/tia.cpp
  riot/riot.cpp
)
target_sources(a26 PRIVATE ${a26_PRIMARY_SOURCES})

ares_add_components(CORE a26 COMPONENT processor/mos6502)

target_sources(a26 PRIVATE a26.hpp CMakeLists.txt)

target_sources(
  a26
  PRIVATE
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
    cartridge/board/atari16k.cpp
    cartridge/board/atari32k.cpp
    cartridge/board/atari8k.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/commavid.cpp
    cartridge/board/linear.cpp
    cartridge/board/parker-bros.cpp
    cartridge/board/tigervision.cpp
)

target_sources(
  a26
  PRIVATE
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  a26
  PRIVATE cpu/cpu.hpp cpu/debugger.cpp cpu/memory.cpp cpu/serialization.cpp cpu/timing.cpp
)

target_sources(a26 PRIVATE riot/io.cpp riot/riot.hpp riot/serialization.cpp)

target_sources(a26 PRIVATE system/controls.cpp system/serialization.cpp system/system.hpp)

target_sources(
  a26
  PRIVATE
    tia/audio.cpp
    tia/ball.cpp
    tia/color.cpp
    tia/io.cpp
    tia/missile.cpp
    tia/player.cpp
    tia/playfield.cpp
    tia/serialization.cpp
    tia/tia.hpp
    tia/write-queue.cpp
)

organize_core_sources(CORE a26)
