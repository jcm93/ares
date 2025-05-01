#if defined(Hiro_Toolbar)

@interface CocoaToolbar : NSToolbar <NSToolbarDelegate> {
@public
  hiro::mToolbar* hiroToolbar;
  NSMutableArray<NSString *> *allowedIdentifiers;
  NSMutableDictionary *identifierImages;
}
-(id) initWith:(hiro::mToolbar&)toolbar;
- (NSMutableArray<NSString *> *) allowedIdentifiers;
- (NSMutableDictionary *) identifierImages;
- (NSArray<NSString *> *) toolbarAllowedItemIdentifiers:(NSToolbar *) toolbar;
- (NSArray<NSString *> *) toolbarDefaultItemIdentifiers:(NSToolbar *) toolbar;
- (NSToolbarItem *) toolbar:(NSToolbar *) toolbar
      itemForItemIdentifier:(NSToolbarItemIdentifier) itemIdentifier
  willBeInsertedIntoToolbar:(BOOL) flag;
@end

@interface CocoaToolbarItem : NSToolbarItem <NSToolbarItemValidation> {
@public
  hiro::mToolbar* hiroToolbar;
  hiro::pToolbarItem* hiroToolbarItem;
  CocoaToolbar* cocoaToolbar;
}
- (void) hiroToolbarAction;
- (id) initWithItemIdentifier:(NSString *)identifier toolbarReference:(hiro::mToolbar&)ToolbarReference;
- (hiro::pToolbarItem *) hiroToolbarItem;
- (void) setHiroToolbarItem:(hiro::pToolbarItem *)item;
- (void) validate;
@end

namespace hiro {

struct pToolbar : pWidget {
  Declare(Toolbar, Widget)

  auto append(sToolbarItem item) -> void;
  auto setWindow(sWindow window) -> void;
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
