#if defined(Hiro_ComboEdit)

namespace hiro {

auto pComboEditItem::construct() -> void {
}

auto pComboEditItem::destruct() -> void {
}

auto pComboEditItem::setIcon(const image& icon) -> void {
}

auto pComboEditItem::setText(const string& text) -> void {
  if(auto parent = _parent()) {
    [[(CocoaComboEdit*)(parent->cocoaView) itemObjectValueAtIndex:self().offset()] setTitle:[NSString stringWithUTF8String:text]];
  }
}

auto pComboEditItem::_parent() -> maybe<pComboEdit&> {
  if(auto parent = self().parentComboEdit()) {
    if(auto self = parent->self()) return *self;
  }
  return nothing;
}

}

#endif
