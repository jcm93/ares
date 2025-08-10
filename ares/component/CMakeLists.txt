macro(add_component_target component)
  add_library(${component} OBJECT ${component}.cpp)
  add_library(ares::component::${component} ALIAS ${component})
  set_target_properties(${component} PROPERTIES OUTPUT_NAME component-${component})
  target_include_directories(${component} PRIVATE ${CMAKE_SOURCE_DIR}/ares)
  target_link_libraries(${component} PRIVATE nall libco)
endmacro()

macro(organize_component_sources component component_type)
  get_target_property(${component}_SOURCES ${component} SOURCES)
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${component}_SOURCES})
  set_source_files_properties(${${component}_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
  set_source_files_properties(${component} ${component}.cpp PROPERTIES HEADER_FILE_ONLY FALSE)
  set_target_properties(${component} PROPERTIES FOLDER ares/component/${component_type} PREFIX "")
endmacro()

list(REMOVE_DUPLICATES ARES_COMPONENTS)

set(ARES_COMPONENTS_LIST "${ARES_COMPONENTS}" CACHE LIST "Enabled shared hardware components" FORCE)
list(SORT ARES_COMPONENTS_LIST ORDER ASCENDING)

foreach(component IN ITEMS ${ARES_COMPONENTS_LIST})
  add_subdirectory(${component})
endforeach()
