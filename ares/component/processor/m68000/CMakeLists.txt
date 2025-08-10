add_component_target(m68000)

target_sources(
  m68000
  PRIVATE
    m68000.cpp
    algorithms.cpp
    conditions.cpp
    disassembler.cpp
    effective-address.cpp
    instruction.cpp
    instructions.cpp
    m68000.hpp
    memory.cpp
    registers.cpp
    serialization.cpp
    traits.cpp
)

organize_component_sources(m68000 processor)
