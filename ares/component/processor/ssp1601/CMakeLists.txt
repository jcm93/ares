add_component_target(ssp1601)

target_sources(
  ssp1601
  PRIVATE
    ssp1601.cpp
    algorithms.cpp
    disassembler.cpp
    instructions.cpp
    memory.cpp
    registers.cpp
    serialization.cpp
    ssp1601.hpp
)

organize_component_sources(ssp1601 processor)
