add_component_target(v9938)

target_sources(
  v9938
  PRIVATE v9938.cpp background.cpp commands.cpp dac.cpp io.cpp serialization.cpp sprite.cpp v9938.hpp
)

organize_component_sources(v9938 video)
