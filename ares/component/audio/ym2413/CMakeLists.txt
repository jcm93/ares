add_component_target(ym2413)

target_sources(
  ym2413
  PRIVATE ym2413.cpp constants.cpp io.cpp operator.cpp serialization.cpp voice.cpp ym2413.hpp
)

organize_component_sources(ym2413 audio)
