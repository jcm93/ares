add_core_target(ps1)

set(
  ps1_PRIMARY_SOURCES
  memory/memory.cpp
  system/system.cpp
  disc/disc.cpp
  cpu/cpu.cpp
  gpu/gpu.cpp
  spu/spu.cpp
  mdec/mdec.cpp
  interrupt/interrupt.cpp
  peripheral/peripheral.cpp
  dma/dma.cpp
  timer/timer.cpp
)
target_sources(ps1 PRIVATE ${ps1_PRIMARY_SOURCES})

ares_add_components(CORE ps1 COMPONENTS processor/m68hc05)

target_sources(
  ps1
  PRIVATE #
    ps1.hpp
    CMakeLists.txt
)

target_sources(
  ps1
  PRIVATE #
    accuracy.hpp
)

target_sources(
  ps1
  PRIVATE #
    cpu/breakpoints.cpp
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/delay-slots.cpp
    cpu/disassembler.cpp
    cpu/exceptions.cpp
    cpu/icache.cpp
    cpu/interpreter-gte.cpp
    cpu/interpreter-ipu.cpp
    cpu/interpreter-scc.cpp
    cpu/interpreter.cpp
    cpu/memory.cpp
    cpu/serialization.cpp
)

target_sources(
  ps1
  PRIVATE #
    disc/cdda.cpp
    disc/cdxa.cpp
    disc/command.cpp
    disc/debugger.cpp
    disc/disc.hpp
    disc/drive.cpp
    disc/io.cpp
    disc/irq.cpp
    disc/serialization.cpp
)

target_sources(
  ps1
  PRIVATE #
    dma/channel.cpp
    dma/debugger.cpp
    dma/dma.hpp
    dma/io.cpp
    dma/irq.cpp
    dma/serialization.cpp
)

target_sources(
  ps1
  PRIVATE #
    gpu/blitter.cpp
    gpu/debugger.cpp
    gpu/gp0.cpp
    gpu/gp1.cpp
    gpu/gpu.hpp
    gpu/io.cpp
    gpu/renderer.cpp
    gpu/serialization.cpp
)

target_sources(
  ps1
  PRIVATE #
    interrupt/interrupt.hpp
    interrupt/io.cpp
    interrupt/serialization.cpp
)

target_sources(
  ps1
  PRIVATE #
    mdec/decoder.cpp
    mdec/io.cpp
    mdec/mdec.hpp
    mdec/serialization.cpp
    mdec/tables.cpp
)

target_sources(
  ps1
  PRIVATE #
    memory/bus.hpp
    memory/interface.hpp
    memory/io.cpp
    memory/memory.hpp
    memory/readable.hpp
    memory/serialization.cpp
    memory/unmapped.hpp
    memory/writable.hpp
)

target_sources(
  ps1
  PRIVATE #
    peripheral/io.cpp
    peripheral/peripheral.hpp
    peripheral/port.cpp
    peripheral/port.hpp
    peripheral/serialization.cpp
    peripheral/digital-gamepad/digital-gamepad.cpp
    peripheral/digital-gamepad/digital-gamepad.hpp
    peripheral/dualshock/dualshock.cpp
    peripheral/dualshock/dualshock.hpp
    peripheral/memory-card/memory-card.cpp
    peripheral/memory-card/memory-card.hpp
)

target_sources(
  ps1
  PRIVATE #
    spu/adpcm.cpp
    spu/adsr.cpp
    spu/capture.cpp
    spu/debugger.cpp
    spu/envelope.cpp
    spu/fifo.cpp
    spu/gaussian.cpp
    spu/io.cpp
    spu/noise.cpp
    spu/reverb.cpp
    spu/serialization.cpp
    spu/spu.hpp
    spu/voice.cpp
)

target_sources(
  ps1
  PRIVATE #
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  ps1
  PRIVATE #
    timer/io.cpp
    timer/serialization.cpp
    timer/timer.hpp
)

organize_core_sources(CORE ps1)
