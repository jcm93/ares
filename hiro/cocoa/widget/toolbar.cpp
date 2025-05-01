#if defined(Hiro_Toolbar)
@implementation CocoaToolbar

-(id) initWith:(hiro::mToolbar&)ToolbarReference {
  if(self = [super initWithFrame:NSMakeRect(0, 0, 0, 0)]) {
    Toolbar = &ToolbarReference;
    //[(NSToolbarController *)self setTabStyle:NSToolbarControllerTabStyleToolbar];

    [self setDelegate:self];
  }
  return self;
}

-(void) tabView:(NSToolbar*)tabView didSelectTabViewItem:(NSToolbarItem*)tabViewItem {
  Toolbar->self()->_synchronizeSizable();
  Toolbar->doChange();
}

@end

@implementation CocoaToolbarItem : NSToolbarItem

-(id) initWith:(hiro::mToolbar&)ToolbarReference {
  if(self = [super initWithIdentifier:nil]) {
    Toolbar = &ToolbarReference;
    cocoaToolbar = Toolbar->self()->cocoaToolbar;
  }
  return self;
}

-(NSSize) sizeOfLabel:(BOOL)shouldTruncateLabel {
  NSSize sizeOfLabel = [super sizeOfLabel:shouldTruncateLabel];
  s32 selection = [cocoaToolbar indexOfTabViewItem:self];
  if(selection >= 0) {
    if(auto item = Toolbar->item(selection)) {
      if(item->state.icon) {
        u32 iconSize = hiro::pFont::size(Toolbar->font(true), " ").height();
        u32 labelWidth = hiro::pFont::size(Toolbar->font(true), self.label.UTF8String).width();
        sizeOfLabel.width += iconSize + labelWidth / 3;
      }
    }
  }
  return sizeOfLabel;
}

-(void) drawLabel:(BOOL)shouldTruncateLabel inRect:(NSRect)tabRect {
  s32 selection = [cocoaToolbar indexOfTabViewItem:self];
  if(selection >= 0) {
    if(auto item = Toolbar->item(selection)) {
      if(item->state.icon) {
        u32 iconSize = hiro::pFont::size(Toolbar->font(true), " ").height();
        u32 labelWidth = hiro::pFont::size(Toolbar->font(true), self.label.UTF8String).width();
        NSImage* image = NSMakeImage(item->state.icon);

        [[NSGraphicsContext currentContext] saveGraphicsState];
        NSRect targetRect = NSMakeRect(tabRect.origin.x, tabRect.origin.y + 2, iconSize, iconSize);
        [image drawInRect:targetRect fromRect:NSZeroRect operation:NSCompositingOperationSourceOver fraction:1.0 respectFlipped:YES hints:nil];
        [[NSGraphicsContext currentContext] restoreGraphicsState];

        tabRect.origin.x += iconSize + 2;
        tabRect.size.width -= iconSize + 2;
      }
    }
  }
  [super drawLabel:shouldTruncateLabel inRect:tabRect];
}

@end

namespace hiro {

auto pToolbar::construct() -> void {
  cocoaView = cocoaToolbar = [[CocoaToolbar alloc] initWith:self()];
  
  pWidget::construct();

  setNavigation(state().navigation);
}

auto pToolbar::destruct() -> void {
  [cocoaView removeFromSuperview];
}

auto pToolbar::append(sToolbarItem item) -> void {
  if(auto p = item->self()) {
    p->cocoaToolbarItem = [[CocoaToolbarItem alloc] initWith:self()];
    [p->cocoaToolbarItem setLabel:[NSString stringWithUTF8String:item->state.text]];
    [(CocoaToolbar*)cocoaView addTabViewItem:p->cocoaToolbarItem];
  }
}

auto pToolbar::remove(sToolbarItem item) -> void {
  if(auto p = item->self()) {
    [(CocoaToolbar*)cocoaView removeTabViewItem:p->cocoaToolbarItem];
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
  NSToolbarItem* tabViewItem = [(CocoaToolbar*)cocoaView selectedTabViewItem];
  s32 selected = tabViewItem ? [(CocoaToolbar*)cocoaView indexOfTabViewItem:tabViewItem] : -1;
  for(auto& item : state().items) {
    item->state.selected = item->offset() == selected;
    if(auto& sizable = item->state.sizable) sizable->setVisible(item->selected());
  }
}

}

#endif
