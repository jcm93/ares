add_component_target(ay38910)

target_sources(ay38910 PRIVATE ay38910.cpp ay38910.hpp serialization.cpp)

organize_component_sources(ay38910 audio)
