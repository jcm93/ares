add_component_target(upd96050)

target_sources(
  upd96050
  PRIVATE upd96050.cpp disassembler.cpp instructions.cpp memory.cpp serialization.cpp upd96050.hpp
)

organize_component_sources(upd96050 processor)
