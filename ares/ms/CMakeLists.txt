add_core_target(ms)

set(
  ms_PRIMARY_SOURCES
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  opll/opll.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  expansion/expansion.cpp
)

target_sources(ms PRIVATE ${ms_PRIMARY_SOURCES})

ares_add_components(CORE ms COMPONENT processor/z80 audio/sn76489 audio/ym2413)

target_sources(
  ms
  PRIVATE #
    ms.hpp
    CMakeLists.txt
)

target_sources(
  ms
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  ms
  PRIVATE #
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/codemasters.cpp
    cartridge/board/hap2000.cpp
    cartridge/board/hicom.cpp
    cartridge/board/janggun.cpp
    cartridge/board/k188in1.cpp
    cartridge/board/korea.cpp
    cartridge/board/pak4.cpp
    cartridge/board/sega.cpp
    cartridge/board/zemina.cpp
)

target_sources(
  ms
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/light-phaser/light-phaser.cpp
    controller/light-phaser/light-phaser.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/md-control-pad/md-control-pad.cpp
    controller/md-control-pad/md-control-pad.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/md-fighting-pad/md-fighting-pad.cpp
    controller/md-fighting-pad/md-fighting-pad.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/mega-mouse/mega-mouse.cpp
    controller/mega-mouse/mega-mouse.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/paddle/paddle.cpp
    controller/paddle/paddle.hpp
)

target_sources(
  ms
  PRIVATE #
    controller/sports-pad/sports-pad.cpp
    controller/sports-pad/sports-pad.hpp
)

target_sources(
  ms
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  ms
  PRIVATE #
    expansion/expansion.hpp
    expansion/port.cpp
    expansion/port.hpp
)

target_sources(
  ms
  PRIVATE #
    expansion/fmsound/fmsound.cpp
    expansion/fmsound/fmsound.hpp
)

target_sources(
  ms
  PRIVATE #
    opll/opll.hpp
    opll/serialization.cpp
)

target_sources(
  ms
  PRIVATE #
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  ms
  PRIVATE #
    system/bios.cpp
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  ms
  PRIVATE #
    vdp/background.cpp
    vdp/color.cpp
    vdp/dac.cpp
    vdp/debugger.cpp
    vdp/io.cpp
    vdp/irq.cpp
    vdp/serialization.cpp
    vdp/sprite.cpp
    vdp/vdp.hpp
)

organize_core_sources(CORE ms)

set_target_properties(ms PROPERTIES FOLDER ares PREFIX "")
