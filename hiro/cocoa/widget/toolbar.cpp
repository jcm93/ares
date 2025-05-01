#if defined(Hiro_Toolbar)
@implementation CocoaToolbar

-(id) initWith:(hiro::mToolbar&)ToolbarReference {
  if(self = [super init]) {
    Toolbar = &ToolbarReference;
    allowedIdentifiers = [[NSMutableArray alloc] initWithCapacity:10];
    //[(NSToolbarController *)self setTabStyle:NSToolbarControllerTabStyleToolbar];

    [self setDelegate:self];
  }
  return self;
}

-(NSMutableArray<NSString *> *) allowedIdentifiers {
  return allowedIdentifiers;
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
  NSToolbarItem *cocoaToolbarItem = [[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier];
  [cocoaToolbarItem setLabel:itemIdentifier];
  [cocoaToolbarItem setAction:@selector(hiroToolbarAction)];
  [cocoaToolbarItem setAutovalidates:YES];
  [cocoaToolbarItem setEnabled:YES];
  //[toolbar insertItemWithItemIdentifier:p->cocoaToolbarItem.label atIndex:0];
  return cocoaToolbarItem;
}

- (void) hiroToolbarAction {
  
}

@end

@implementation CocoaToolbarItem : NSToolbarItem

-(id) initWith:(hiro::mToolbar&)ToolbarReference {
  if(self = [super initWithItemIdentifier:@"poop"]) {
    Toolbar = &ToolbarReference;
    cocoaToolbar = Toolbar->self()->cocoaToolbar;
  }
  return self;
}

- (void) validate {
  print("validating");
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
  [cocoaToolbar setVisible:YES];
}

auto pToolbar::destruct() -> void {
  [cocoaView removeFromSuperview];
}

auto pToolbar::append(sToolbarItem item) -> void {
  if(auto p = item->self()) {
    p->cocoaToolbarItem = [[CocoaToolbarItem alloc] initWith:self()];
    [p->cocoaToolbarItem setLabel:[NSString stringWithUTF8String:item->state.text]];
    [cocoaToolbar insertItemWithItemIdentifier:p->cocoaToolbarItem.label atIndex:0];
    [[cocoaToolbar allowedIdentifiers] addObject:[NSString stringWithUTF8String:item->state.text]];
    [cocoaToolbar setVisible:YES];
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
