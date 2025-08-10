add_component_target(m93lcx6)

target_sources(m93lcx6 PRIVATE m93lcx6.cpp m93lcx6.hpp serialization.cpp)

organize_component_sources(m93lcx6 eeprom)
