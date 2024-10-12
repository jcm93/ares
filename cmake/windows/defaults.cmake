set(ARES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(ARES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(ARES_EXECUTABLE_DESTINATION ${ARES_OUTPUT_DIR})
set(ARES_LIBRARY_DESTINATION lib)
set(ARES_INCLUDE_DESTINATION include)
# Set relative paths used by ares for self-discovery
set(ARES_DATA_PATH "../../${ARES_DATA_DESTINATION}")

set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL TRUE)

# Small hack: under MSYS2, CMake looks for .dll.a files rather than .dll files; tell it to also look for .dll files
set(CMAKE_FIND_LIBRARY_SUFFIXES .dll ${CMAKE_FIND_LIBRARY_SUFFIXES})

include(dependencies)
