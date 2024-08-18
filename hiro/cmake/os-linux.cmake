if(platform STREQUAL linux OR platform STREQUAL bsd)
  if(NOT hiro)
    set(hiro gtk3)
  endif()

  if(hiro STREQUAL gtk2)
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=2 $(shell $(PKG_CONFIG) --cflags gtk+-2.0) -Wno-deprecated-declarations
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs gtk+-2.0)
  endif()

  if(hiro STREQUAL gtk2-se)
#    flags       += -DHiro_SourceEdit
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=2 $(shell $(PKG_CONFIG) --cflags gtk+-2.0 gtksourceview-2.0) -Wno-deprecated-declarations
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs gtk+-2.0 gtksourceview-2.0)
  endif()

  if(hiro STREQUAL gtk3)
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=3 $(shell $(PKG_CONFIG) --cflags gtk+-3.0) -Wno-deprecated-declarations
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs gtk+-3.0)
  endif()

  if(hiro STREQUAL gtk3-se)
#    flags       += -DHiro_SourceEdit
#    hiro.flags   = $(flags.cpp) -DHIRO_GTK=3 $(shell $(PKG_CONFIG) --cflags gtk+-3.0 gtksourceview-3.0) -Wno-deprecated-declarations
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs gtk+-3.0 gtksourceview-3.0)
  endif()

  if(hiro STREQUAL qt4)
#    moc = /usr/local/lib/qt4/bin/moc
#    hiro.flags   = $(flags.cpp) -DHIRO_QT=4 $(shell $(PKG_CONFIG) --cflags QtCore QtGui)
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs QtCore QtGui)
  endif()

  if(hiro STREQUAL qt5)
#    moc = $(shell $(PKG_CONFIG) --variable=host_bins Qt5Core)/moc
#    hiro.flags   = $(flags.cpp) -DHIRO_QT=5 -fPIC $(shell $(PKG_CONFIG) --cflags Qt5Core Qt5Gui Qt5Widgets)
#    hiro.options = -L/usr/local/lib -lX11 $(shell $(PKG_CONFIG) --libs Qt5Core Qt5Gui Qt5Widgets)
  endif()
endif()
