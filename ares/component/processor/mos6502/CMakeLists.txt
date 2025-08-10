add_component_target(mos6502)

target_sources(
  mos6502
  PRIVATE
    addresses.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    mos6502.hpp
    serialization.cpp
)

organize_component_sources(mos6502 processor)
