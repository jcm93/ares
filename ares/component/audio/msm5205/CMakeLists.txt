add_component_target(msm5205)

target_sources(msm5205 PRIVATE msm5205.cpp msm5205.hpp serialization.cpp)

organize_component_sources(msm5205 audio)
