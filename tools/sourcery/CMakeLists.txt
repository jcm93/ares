add_executable(sourcery sourcery.cpp)

target_include_directories(sourcery PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(sourcery PRIVATE nall "$<LINK_LIBRARY:FRAMEWORK,Cocoa.framework>")
set_target_properties(sourcery PROPERTIES FOLDER tools PREFIX "")
