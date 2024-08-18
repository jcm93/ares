set(hiro cocoa)
          
target_sources(
  hiro
  PRIVATE cmake/os-macos.cmake)
  
target_enable_feature(hiro "Cocoa UI backend" HIRO_COCOA)
          
target_compile_definitions(
  hiro
  PRIVATE PLATFORM_MACOS)
          
target_link_libraries(
  ruby
  PRIVATE # cmake-format: sortable
          "$<LINK_LIBRARY:FRAMEWORK,Cocoa.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,Carbon.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,IOKit.framework>"
          "$<LINK_LIBRARY:FRAMEWORK,Security.framework>")
          
get_target_property(hiro_SOURCES hiro SOURCES)
          
set_source_files_properties(
  hiro
  ${hiro_SOURCES}
  PROPERTIES
  HEADER_FILE_ONLY
  TRUE)
  
set_source_files_properties(
  hiro
  hiro.cpp
  PROPERTIES
  HEADER_FILE_ONLY
  FALSE)
  
# Explicitly mark hiro.cpp as Objective-C++
set_source_files_properties(
  hiro
  hiro.cpp
  PROPERTIES
  XCODE_EXPLICIT_FILE_TYPE
  sourcecode.cpp.objcpp)  
