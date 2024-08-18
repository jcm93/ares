if(NOT hiro)
  set(hiro windows)
endif()

target_compile_definitions(hiro PRIVATE HIRO_WINDOWS)
target_link_libraries(hiro PRIVATE kernel32 user32 gdi32 advapi32 ole32 comctl32 comdlg32 uxtheme msimg32 dwmapi)



  if(hiro STREQUAL gtk2)
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=2 $(shell pkg-config --cflags gtk+-2.0) -Wno-deprecated-declarations
#    hiro.options = $(shell pkg-config --libs gtk+-2.0)
  endif()

  if(hiro STREQUAL gtk3)
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=3 $(shell pkg-config --cflags gtk+-3.0) -Wno-deprecated-declarations
#    hiro.options = $(shell pkg-config --libs gtk+-3.0)
  endif()
  
if(NOT hiro.resource)
  set(hiro.resource windows/hiro.rc)
endif()
