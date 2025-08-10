add_component_target(sn76489)

target_sources(sn76489 PRIVATE sn76489.cpp sn76489.hpp serialization.cpp)

organize_component_sources(sn76489 audio)
