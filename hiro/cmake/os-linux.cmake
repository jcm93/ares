target_compile_definitions(hiro PRIVATE HIRO_GTK)
find_package(GTK)
find_package(GLib)
find_package(X11)
target_link_libraries(hiro PRIVATE GTK::GTK X11::X11)
target_enable_feature(hiro "GTK3 UI backend" HIRO_GTK=3)
# target_compile_options(hiro PRIVATE -Wl,--copy-dt-needed-entries)

get_target_property(hiro_SOURCES hiro SOURCES)

set_source_files_properties(hiro ${hiro_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_source_files_properties(hiro hiro.cpp PROPERTIES HEADER_FILE_ONLY FALSE)
