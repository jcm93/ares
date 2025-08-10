add_component_target(spc700)

target_sources(
  spc700
  PRIVATE
    spc700.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    serialization.cpp
    spc700.hpp
)

organize_component_sources(spc700 processor)
