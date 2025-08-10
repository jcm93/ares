add_component_target(sm5k)

target_sources(
  sm5k
  PRIVATE sm5k.cpp disassembler.cpp instruction.cpp instructions.cpp memory.cpp serialization.cpp sm5k.hpp timer.cpp
)

organize_component_sources(sm5k processor)
