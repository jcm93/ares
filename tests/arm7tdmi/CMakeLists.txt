if(TARGET arm7tdmi)
  add_executable(arm7tdmi-test arm7tdmi.cpp)

  target_include_directories(arm7tdmi-test PRIVATE ${CMAKE_SOURCE_DIR})

  set(ARM7TDMI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/ares/component/processor/arm7tdmi")

  target_sources(
    arm7tdmi-test
    PRIVATE
      ${ARM7TDMI_SOURCE_DIR}/algorithms.cpp
      ${ARM7TDMI_SOURCE_DIR}/arm7tdmi.hpp
      ${ARM7TDMI_SOURCE_DIR}/disassembler.cpp
      ${ARM7TDMI_SOURCE_DIR}/instruction.cpp
      ${ARM7TDMI_SOURCE_DIR}/instructions-arm.cpp
      ${ARM7TDMI_SOURCE_DIR}/instructions-thumb.cpp
      ${ARM7TDMI_SOURCE_DIR}/memory.cpp
      ${ARM7TDMI_SOURCE_DIR}/registers.cpp
      ${ARM7TDMI_SOURCE_DIR}/serialization.cpp
      ${ARM7TDMI_SOURCE_DIR}/algorithms.cpp
      ${ARM7TDMI_SOURCE_DIR}/arm7tdmi.hpp
      clone-tests.sh
      run-tests.sh
  )

  set_target_properties(arm7tdmi-test PROPERTIES FOLDER tests PREFIX "")
  get_target_property(arm7tdmi_SOURCES arm7tdmi-test SOURCES)
  list(REMOVE_ITEM arm7tdmi_SOURCES arm7tdmi.cpp)
  set_source_files_properties(${arm7tdmi_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

  target_enable_subproject(arm7tdmi-test "arm7tdmi processor test harness")

  target_link_libraries(arm7tdmi-test PRIVATE ares::nall ares::headers ares::ares) # ares::nall)
  set(CONSOLE TRUE)
  ares_configure_executable(arm7tdmi-test)

  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES arm7tdmi.cpp)
endif()
