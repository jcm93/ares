add_component_target(v30mz)

target_sources(
  v30mz
  PRIVATE
    v30mz.cpp
    algorithms.cpp
    disassembler.cpp
    instruction.cpp
    instructions-adjust.cpp
    instructions-alu.cpp
    instructions-exec.cpp
    instructions-flag.cpp
    instructions-group.cpp
    instructions-misc.cpp
    instructions-move.cpp
    instructions-string.cpp
    memory.cpp
    modrm.cpp
    prefetch.cpp
    registers.cpp
    serialization.cpp
    v30mz.hpp
)

organize_component_sources(v30mz processor)
