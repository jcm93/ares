add_component_target(wdc65816)

target_sources(
  wdc65816
  PRIVATE
    wdc65816.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instruction.hpp
    instructions-modify.cpp
    instructions-other.cpp
    instructions-pc.cpp
    instructions-read.cpp
    instructions-write.cpp
    memory.cpp
    registers.hpp
    serialization.cpp
    wdc65816.hpp
)

organize_component_sources(wdc65816 processor)
