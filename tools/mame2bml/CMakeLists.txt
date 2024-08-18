add_executable(mame2bml mame2bml.cpp)

target_include_directories(mame2bml PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(mame2bml PRIVATE nall)
