add_component_target(z80)

target_sources(
  z80
  PRIVATE
    z80.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    registers.hpp
    serialization.cpp
    z80.hpp
)

organize_component_sources(z80 processor)
