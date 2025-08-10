add_component_target(huc6280)

target_sources(
  huc6280
  PRIVATE
    huc6280.cpp
    algorithms.cpp
    disassembler.cpp
    huc6280.hpp
    instruction.cpp
    instructions.cpp
    memory.cpp
    serialization.cpp
)

organize_component_sources(huc6280 processor)
