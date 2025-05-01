#if defined(Hiro_Toolbar)

@interface CocoaToolbar : NSToolbar <NSToolbarDelegate> {
@public
  hiro::mToolbar* Toolbar;
}
-(id) initWith:(hiro::mToolbar&)Toolbar;
-(void) tabView:(NSToolbar*)tabView didSelectTabViewItem:(NSToolbarItem*)tabViewItem;
@end

@interface CocoaToolbarItem : NSToolbarItem {
@public
  hiro::mToolbar* Toolbar;
  CocoaToolbar* cocoaToolbar;
}
-(id) initWith:(hiro::mToolbar&)Toolbar;
-(NSSize) sizeOfLabel:(BOOL)shouldTruncateLabel;
-(void) drawLabel:(BOOL)shouldTruncateLabel inRect:(NSRect)tabRect;
@end

namespace hiro {

struct pToolbar : pWidget {
  Declare(Toolbar, Widget)

  auto append(sToolbarItem item) -> void;
  auto remove(sToolbarItem item) -> void;
  auto setEnabled(bool enabled) -> void override;
  auto setFont(const Font& font) -> void override;
  auto setGeometry(Geometry geometry) -> void override;
  auto setNavigation(Navigation navigation) -> void;
  auto setVisible(bool visible) -> void override;

  auto _synchronizeSizable() -> void;

  CocoaToolbar* cocoaToolbar = nullptr;
};

}

#endif
