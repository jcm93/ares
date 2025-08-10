add_library(m68hc05 STATIC m68hc05.cpp)

target_sources(
  m68hc05
  PRIVATE
    processor/m68hc05/m68hc05.cpp
    processor/m68hc05/algorithms.cpp
    processor/m68hc05/disassembler.cpp
    processor/m68hc05/instruction.cpp
    processor/m68hc05/instructions.cpp
    processor/m68hc05/m68hc05.hpp
    processor/m68hc05/memory.cpp
    processor/m68hc05/serialization.cpp
)

get_target_property(m68hc05_SOURCES m68hc05 SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${m68hc05_SOURCES})
set_source_files_properties(${m68hc05_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(m68hc05 m68hc05.cpp PROPERTIES HEADER_FILE_ONLY FALSE)
set_target_properties(m68hc05 PROPERTIES FOLDER ares/component/processor PREFIX "")
target_link_libraries(m68hc05 PRIVATE nall ares)
