add_component_target(ym2149)

target_sources(ym2149 PRIVATE ym2149.cpp ym2149.hpp serialization.cpp)

organize_component_sources(ym2149 audio)
