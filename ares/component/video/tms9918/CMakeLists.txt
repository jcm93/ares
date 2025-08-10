add_component_target(tms9918)

target_sources(
  tms9918
  PRIVATE tms9918.cpp background.cpp dac.cpp io.cpp serialization.cpp sprite.cpp tms9918.hpp
)

organize_component_sources(tms9918 processor)
