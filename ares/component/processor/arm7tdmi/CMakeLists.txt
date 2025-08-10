add_component_target(arm7tdmi)

target_sources(
  arm7tdmi
  PRIVATE
    arm7tdmi.cpp
    algorithms.cpp
    arm7tdmi.hpp
    disassembler.cpp
    instruction.cpp
    instructions-arm.cpp
    instructions-thumb.cpp
    memory.cpp
    registers.cpp
    serialization.cpp
)

organize_component_sources(arm7tdmi processor)
