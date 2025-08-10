add_component_target(tlcs900h)

target_sources(
  tlcs900h
  PRIVATE
    tlcs900h.cpp
    algorithms.cpp
    conditions.cpp
    control-registers.cpp
    disassembler.cpp
    dma.cpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    prefetch.cpp
    registers.cpp
    serialization.cpp
    tlcs900h.hpp
)

organize_component_sources(tlcs900h processor)
