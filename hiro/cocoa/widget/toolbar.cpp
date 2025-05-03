#if defined(Hiro_Toolbar)
@implementation CocoaToolbar

-(id) initWith:(hiro::mToolbar&)toolbarReference {
  if(self = [super init]) {
    hiroToolbar = &toolbarReference;
    allowedIdentifiers = [[NSMutableArray alloc] initWithCapacity:10];
    identifierImages = [[NSMutableDictionary alloc] initWithCapacity:10];

    [self setDelegate:self];
  }
  return self;
}

-(NSMutableArray<NSString *> *) allowedIdentifiers {
  return allowedIdentifiers;
}

- (NSMutableDictionary *) identifierImages {
  return identifierImages;
}

- (NSArray<NSString *> *) toolbarAllowedItemIdentifiers:(NSToolbar *) toolbar {
  return allowedIdentifiers;
}

- (NSArray<NSString *> *) toolbarDefaultItemIdentifiers:(NSToolbar *) toolbar {
  return allowedIdentifiers;
}

- (NSToolbarItem *) toolbar:(NSToolbar *) toolbar
      itemForItemIdentifier:(NSToolbarItemIdentifier) itemIdentifier
willBeInsertedIntoToolbar:(BOOL) flag {
  CocoaToolbarItem *cocoaToolbarItem = [[CocoaToolbarItem alloc] initWithItemIdentifier:itemIdentifier toolbarReference:*hiroToolbar];
  [cocoaToolbarItem setLabel:itemIdentifier];
  [cocoaToolbarItem setImage:(NSImage *)identifierImages[itemIdentifier]];
  [cocoaToolbarItem setTarget:cocoaToolbarItem];
  [cocoaToolbarItem setAction:@selector(hiroToolbarAction)];
  //[toolbar insertItemWithItemIdentifier:p->cocoaToolbarItem.label atIndex:0];
  return cocoaToolbarItem;
}

@end

@implementation CocoaToolbarItem : NSToolbarItem

-(id) initWithItemIdentifier:(NSString *)identifier toolbarReference:(hiro::mToolbar&)ToolbarReference {
  if(self = [super initWithItemIdentifier:identifier]) {
    hiroToolbar = &ToolbarReference;
    cocoaToolbar = hiroToolbar->self()->cocoaToolbar;
  }
  return self;
}

- (void) hiroToolbarAction {
  hiroToolbar->onSelect(self.itemIdentifier.UTF8String);
  hiroToolbar->state.onChange();
  //print("action!");
}

- (void) validate {
}


- (hiro::pToolbarItem *)hiroToolbarItem {
  return hiroToolbarItem;
}

- (void)setHiroToolbarItem:(hiro::pToolbarItem *)item {
  hiroToolbarItem = item;
}

@end

namespace hiro {

auto pToolbar::construct() -> void {
  cocoaToolbar = [[CocoaToolbar alloc] initWith:self()];
  
  pWidget::construct();

  setNavigation(state().navigation);
}

auto pToolbar::setWindow(sWindow window) -> void {
  auto p = window->self();
  p->cocoaWindow.toolbar = cocoaToolbar;
  [p->cocoaWindow toggleToolbarShown:nil];
  if (@available(macOS 11.0, *)) {
    [p->cocoaWindow setToolbarStyle:NSWindowToolbarStylePreference];
  }
  [cocoaToolbar setVisible:YES];
}

auto pToolbar::destruct() -> void {
  [cocoaView removeFromSuperview];
}

auto pToolbar::append(sToolbarItem item) -> void {
  if(auto p = item->self()) {
    auto labelString = [NSString stringWithUTF8String:item->state.text];
    [cocoaToolbar insertItemWithItemIdentifier:labelString atIndex:0];
    [[cocoaToolbar allowedIdentifiers] addObject:labelString];
    [cocoaToolbar identifierImages][labelString] = NSMakeImage(item->icon());
  }
}

auto pToolbar::remove(sToolbarItem item) -> void {
  if(auto p = item->self()) {
    [cocoaToolbar removeItemAtIndex:0];//todo
  }
}

auto pToolbar::setEnabled(bool enabled) -> void {
  pWidget::setEnabled(enabled);
  for(auto& item : state().items) {
    if(auto& sizable = item->state.sizable) {
      if(auto self = sizable->self()) self->setEnabled(sizable->enabled(true));
    }
  }
}

auto pToolbar::setFont(const Font& font) -> void {
  pWidget::setFont(font);
  for(auto& item : state().items) {
    if(auto& sizable = item->state.sizable) {
      if(auto self = sizable->self()) self->setFont(sizable->font(true));
    }
  }
}

auto pToolbar::setGeometry(Geometry geometry) -> void {
  pWidget::setGeometry({
    geometry.x() - 7, geometry.y() - 5,
    geometry.width() + 14, geometry.height() + 6
  });
  geometry.setGeometry({
    geometry.x() + 1, geometry.y() + 22,
    geometry.width() - 2, geometry.height() - 32
  });
  for(auto& item : state().items) {
    if(auto& sizable = item->state.sizable) {
      sizable->setGeometry(geometry);
    }
  }
  _synchronizeSizable();
}

auto pToolbar::setNavigation(Navigation navigation) -> void {
}

auto pToolbar::setVisible(bool visible) -> void {
  pWidget::setVisible(visible);
  for(auto& item : state().items) {
    if(auto& sizable = item->state.sizable) {
      if(auto self = sizable->self()) self->setVisible(sizable->visible(true));
    }
  }
}

auto pToolbar::_synchronizeSizable() -> void {
  
}

}

#endif
