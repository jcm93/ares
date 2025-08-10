add_component_target(hg51b)

target_sources(
  hg51b
  PRIVATE hg51b.cpp disassembler.cpp hg51b.hpp instruction.cpp instructions.cpp registers.cpp serialization.cpp
)

organize_component_sources(hg51b processor)
