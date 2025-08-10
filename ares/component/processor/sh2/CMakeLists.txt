add_component_target(sh2)

target_sources(
  sh2
  PRIVATE
    sh2.cpp
    accuracy.hpp
    decoder.hpp
    disassembler.cpp
    exceptions.cpp
    instruction.cpp
    instructions.cpp
    recompiler.cpp
    serialization.cpp
    sh2.hpp
    sh7604/bus.cpp
    sh7604/cache.cpp
    sh7604/dma.cpp
    sh7604/interrupts.cpp
    sh7604/io.cpp
    sh7604/serial.cpp
    sh7604/sh7604.cpp
    sh7604/sh7604.hpp
    sh7604/timer.cpp
)

organize_component_sources(sh2 processor)
