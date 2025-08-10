add_component_target(sm83)

target_sources(
  sm83
  PRIVATE
    sm83.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    registers.hpp
    serialization.cpp
    sm83.hpp
)

organize_component_sources(sm83 processor)
