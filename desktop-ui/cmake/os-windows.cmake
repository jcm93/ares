target_sources(desktop-ui PRIVATE resource/ares.rc resource/ares.Manifest)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT desktop-ui)

add_custom_command(
  TARGET desktop-ui
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_EXECUTABLE_DESTINATION}/desktop-ui/$<CONFIG>/Shaders/"
  COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/.deps/ares-deps-windows-${arch}/lib/slang-shaders/"
    "${ARES_EXECUTABLE_DESTINATION}/desktop-ui/$<CONFIG>/Shaders/"
  WORKING_DIRECTORY "."
  COMMENT "Copying slang shaders to rundir"
)

if(EXISTS "${CMAKE_SOURCE_DIR}/mia/Database")
  add_custom_command(
    TARGET desktop-ui
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_EXECUTABLE_DESTINATION}/desktop-ui/$<CONFIG>/Database/"
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/mia/Database/"
    "${ARES_EXECUTABLE_DESTINATION}/desktop-ui/$<CONFIG>/Database/"
    COMMENT "Copying mia database to rundir"
  )
endif()