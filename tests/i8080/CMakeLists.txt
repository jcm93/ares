add_executable(i8080
	i8080.cpp
	../../ares/component/processor/i8080/i8080.cpp
)

target_include_directories(i8080 PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(i8080 PRIVATE ${CMAKE_SOURCE_DIR}/ares)

target_link_libraries(i8080 PRIVATE nall ares)
set_target_properties(i8080 PROPERTIES FOLDER tests PREFIX "")
