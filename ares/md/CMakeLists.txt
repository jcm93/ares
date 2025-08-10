add_core_target(md)

set(
  md_PRIMARY_SOURCES
  bus/bus.cpp
  cpu/cpu.cpp
  apu/apu.cpp
  vdp/vdp.cpp
  opn2/opn2.cpp
  m32x/m32x.cpp
  mcd/mcd.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
)
target_sources(md PRIVATE ${md_PRIMARY_SOURCES})

ares_add_components(
  CORE md
  COMPONENT processor/m68000 processor/z80 processor/sh2 processor/ssp1601 audio/sn76489 audio/ym2612 eeprom/m24c
)

target_sources(
  md
  PRIVATE #
    md.hpp
    CMakeLists.txt
)

target_sources(
  md
  PRIVATE #
    apu/apu.hpp
    apu/bus.cpp
    apu/debugger.cpp
    apu/serialization.cpp
)

target_sources(
  md
  PRIVATE #
    bus/bus.hpp
    bus/inline.hpp
    bus/serialization.cpp
)

target_sources(
  md
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
)

target_sources(
  md
  PRIVATE #
    cartridge/board/banked.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/debugger.cpp
    cartridge/board/game-genie.cpp
    cartridge/board/j-cart.cpp
    cartridge/board/linear.cpp
    cartridge/board/mega-32x.cpp
    cartridge/board/realtec.cpp
    cartridge/board/standard.cpp
    cartridge/board/svp.cpp
)

target_sources(
  md
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
)

target_sources(
  md
  PRIVATE #
    controller/control-pad/control-pad.cpp
    controller/control-pad/control-pad.hpp
)

target_sources(
  md
  PRIVATE #
    controller/fighting-pad/fighting-pad.cpp
    controller/fighting-pad/fighting-pad.hpp
)

target_sources(
  md
  PRIVATE #
    cpu/bus.cpp
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/io.cpp
    cpu/serialization.cpp
)

target_sources(
  md
  PRIVATE #
    m32x/bus-external.cpp
    m32x/bus-internal.cpp
    m32x/debugger.cpp
    m32x/io-external.cpp
    m32x/io-internal.cpp
    m32x/m32x.hpp
    m32x/pwm.cpp
    m32x/serialization.cpp
    m32x/sh7604.cpp
    m32x/vdp.cpp
)

target_sources(
  md
  PRIVATE #
    mcd/bus-external.cpp
    mcd/bus-internal.cpp
    mcd/cdc-transfer.cpp
    mcd/cdc.cpp
    mcd/cdd-dac.cpp
    mcd/cdd.cpp
    mcd/debugger.cpp
    mcd/gpu.cpp
    mcd/io-external.cpp
    mcd/io-internal.cpp
    mcd/irq.cpp
    mcd/mcd.hpp
    mcd/pcm.cpp
    mcd/serialization.cpp
    mcd/timer.cpp
)

target_sources(
  md
  PRIVATE #
    opn2/opn2.hpp
    opn2/serialization.cpp
)

target_sources(
  md
  PRIVATE #
    system/controls.cpp
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  md
  PRIVATE #
    vdp/color.cpp
    vdp/dac.cpp
    vdp/debugger.cpp
    vdp/dma.cpp
    vdp/fifo.cpp
    vdp/io.cpp
    vdp/irq.cpp
    vdp/layer.cpp
    vdp/layers.cpp
    vdp/main.cpp
    vdp/memory.cpp
    vdp/prefetch.cpp
    vdp/psg.cpp
    vdp/serialization.cpp
    vdp/sprite.cpp
    vdp/vdp.hpp
    vdp/window.cpp
)

target_sources(
  md
  PRIVATE #
    vdp-performance/background.cpp
    vdp-performance/color.cpp
    vdp-performance/debugger.cpp
    vdp-performance/dma.cpp
    vdp-performance/io.cpp
    vdp-performance/irq.cpp
    vdp-performance/main.cpp
    vdp-performance/memory.cpp
    vdp-performance/object.cpp
    vdp-performance/psg.cpp
    vdp-performance/render.cpp
    vdp-performance/serialization.cpp
    vdp-performance/sprite.cpp
    vdp-performance/vdp.cpp
    vdp-performance/vdp.hpp
)

organize_core_sources(CORE md)

set_target_properties(md PROPERTIES FOLDER ares PREFIX "")
