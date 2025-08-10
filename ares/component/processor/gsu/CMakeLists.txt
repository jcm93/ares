add_component_target(gsu)

target_sources(
  gsu
  PRIVATE gsu.cpp disassembler.cpp gsu.hpp instruction.cpp instructions.cpp registers.hpp serialization.cpp
)

organize_component_sources(gsu processor)
