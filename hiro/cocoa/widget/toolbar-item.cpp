#if defined(Hiro_Toolbar)

namespace hiro {

auto pToolbarItem::construct() -> void {
}

auto pToolbarItem::destruct() -> void {
}

auto pToolbarItem::append(sSizable sizable) -> void {
}

auto pToolbarItem::remove(sSizable sizable) -> void {
}

auto pToolbarItem::setClosable(bool closable) -> void {
}

auto pToolbarItem::setIcon(const image& icon) -> void {
}

auto pToolbarItem::setMovable(bool movable) -> void {
}

auto pToolbarItem::setSelected() -> void {
  if(auto parent = _parent()) {
    auto parentToolbar = parent->cocoaToolbar;
    auto identifierString = [NSString stringWithUTF8String:state().text];
    [parentToolbar setSelectedItemIdentifier:identifierString];
  }
}

auto pToolbarItem::setText(const string& text) -> void {
  [cocoaToolbarItem setLabel:[NSString stringWithUTF8String:state().text]];
}

auto pToolbarItem::_parent() -> maybe<pToolbar&> {
  if(auto parent = self().parentToolbar()) {
    if(auto self = parent->self()) return *self;
  }
  return nothing;
}

}

#endif
