add_core_target(fc)

set(
  fc_PRIMARY_SOURCES
  system/system.cpp
  controller/controller.cpp
  expansion/expansion.cpp
  cartridge/cartridge.cpp
  cpu/cpu.cpp
  apu/apu.cpp
  ppu/ppu.cpp
  fds/fds.cpp
)
target_sources(fc PRIVATE ${fc_PRIMARY_SOURCES})

ares_add_components(
  CORE fc
  COMPONENT processor/mos6502 audio/ym2149 audio/ym2413 eeprom/m24c flash/sst39sf0x0
)

target_link_libraries(fc PRIVATE ymfm)

target_sources(
  fc
  PRIVATE #
    fc.hpp
)

target_sources(
  fc
  PRIVATE #
    apu/apu.hpp
    apu/dmc.cpp
    apu/envelope.cpp
    apu/framecounter.cpp
    apu/length.cpp
    apu/noise.cpp
    apu/pulse.cpp
    apu/serialization.cpp
    apu/sweep.cpp
    apu/triangle.cpp
)

target_sources(
  fc
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  fc
  PRIVATE #
    cartridge/board/action53.cpp
    cartridge/board/ave-nina-001.cpp
    cartridge/board/ave-nina-06.cpp
    cartridge/board/bandai-74161.cpp
    cartridge/board/bandai-fcg.cpp
    cartridge/board/bandai-karaoke.cpp
    cartridge/board/bandai-lz93d50.cpp
    cartridge/board/bandai-oeka.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/camerica-bf909x.cpp
    cartridge/board/colordreams-74x377.cpp
    cartridge/board/gtrom.cpp
    cartridge/board/hvc-axrom.cpp
    cartridge/board/hvc-bnrom.cpp
    cartridge/board/hvc-cnrom.cpp
    cartridge/board/hvc-exrom.cpp
    cartridge/board/hvc-fmr.cpp
    cartridge/board/hvc-fxrom.cpp
    cartridge/board/hvc-gxrom.cpp
    cartridge/board/hvc-hkrom.cpp
    cartridge/board/hvc-nrom.cpp
    cartridge/board/hvc-pxrom.cpp
    cartridge/board/hvc-sxrom.cpp
    cartridge/board/hvc-txrom.cpp
    cartridge/board/hvc-uxrom.cpp
    cartridge/board/inl-nsf.cpp
    cartridge/board/irem-g101.cpp
    cartridge/board/irem-h3001.cpp
    cartridge/board/irem-lrog017.cpp
    cartridge/board/irem-tam-s1.cpp
    cartridge/board/jaleco-jf05.cpp
    cartridge/board/jaleco-jf11.cpp
    cartridge/board/jaleco-jf16.cpp
    cartridge/board/jaleco-jf17.cpp
    cartridge/board/jaleco-jf23.cpp
    cartridge/board/konami-vrc1.cpp
    cartridge/board/konami-vrc2.cpp
    cartridge/board/konami-vrc3.cpp
    cartridge/board/konami-vrc4.cpp
    cartridge/board/konami-vrc5.cpp
    cartridge/board/konami-vrc6.cpp
    cartridge/board/konami-vrc7.cpp
    cartridge/board/magicfloor.cpp
    cartridge/board/mlt-action52.cpp
    cartridge/board/namco-118.cpp
    cartridge/board/namco-163.cpp
    cartridge/board/namco-340.cpp
    cartridge/board/sunsoft-1.cpp
    cartridge/board/sunsoft-2.cpp
    cartridge/board/sunsoft-3.cpp
    cartridge/board/sunsoft-4.cpp
    cartridge/board/sunsoft-5b.cpp
    cartridge/board/taito-tc0190.cpp
    cartridge/board/taito-tc0690.cpp
    cartridge/board/taito-x1-005.cpp
    cartridge/board/taito-x1-017.cpp
    cartridge/board/tengen-80003x.cpp
    cartridge/board/unl-bmc.cpp
    cartridge/board/unl-sachen-74ls374n.cpp
    cartridge/board/unl-sachen-sa0037.cpp
    cartridge/board/unl-txc.cpp
    cartridge/board/unrom-512.cpp
)

target_sources(
  fc
  PRIVATE #
    cartridge/board/ic/jv001.hpp
    cartridge/board/ic/txc05-00002-010.hpp
)

target_sources(
  fc
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  fc
  PRIVATE #
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
)

target_sources(
  fc
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
    cpu/timing.cpp
)

target_sources(
  fc
  PRIVATE #
    expansion/expansion.hpp
    expansion/port.cpp
    expansion/port.hpp
)

target_sources(
  fc
  PRIVATE #
    expansion/epsm/epsm.cpp
    expansion/epsm/epsm.hpp
)

target_sources(
  fc
  PRIVATE #
    expansion/family-keyboard/family-keyboard.cpp
    expansion/family-keyboard/family-keyboard.hpp
)

target_sources(
  fc
  PRIVATE #
    fds/audio.cpp
    fds/audio.hpp
    fds/drive.cpp
    fds/drive.hpp
    fds/fds.hpp
    fds/serialization.cpp
    fds/timer.cpp
    fds/timer.hpp
)

target_sources(
  fc
  PRIVATE #
    ppu/color.cpp
    ppu/debugger.cpp
    ppu/memory.cpp
    ppu/ppu.hpp
    ppu/render.cpp
    ppu/scroll.cpp
    ppu/serialization.cpp
    ppu/sprite.cpp
)

target_sources(
  fc
  PRIVATE #
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

organize_core_sources(CORE fc)
