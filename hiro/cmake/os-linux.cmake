target_compile_definitions(hiro PRIVATE HIRO_GTK)
find_package(cairo)
find_package(GTK)
find_package(GLib)
target_link_libraries(hiro PRIVATE GTK::GTK cairo::cairo GLib::GLib)

# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLIB REQUIRED glib-2.0)
# target_include_directories(hiro PRIVATE ${GLIB_INCLUDE_DIRS})
# message(AUTHOR_WARNING "glib ldflags are ${GLIB_LDFLAGS}")
# target_link_libraries(hiro INTERFACE ${GLIB_LDFLAGS}) # why
