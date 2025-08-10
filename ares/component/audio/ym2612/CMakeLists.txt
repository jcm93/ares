add_component_target(ym2612)

target_sources(
  ym2612
  PRIVATE ym2612.cpp channel.cpp constants.cpp io.cpp serialization.cpp timer.cpp ym2612.hpp
)

organize_component_sources(ym2612 audio)
