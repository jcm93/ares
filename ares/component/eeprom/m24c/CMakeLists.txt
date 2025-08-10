add_component_target(m24c)

target_sources(m24c PRIVATE m24c.cpp m24c.hpp serialization.cpp)

organize_component_sources(m24c audio)
