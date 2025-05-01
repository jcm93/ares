#if defined(Hiro_Toolbar)

auto mToolbarItem::allocate() -> pObject* {
  return new pToolbarItem(*this);
}

auto mToolbarItem::destruct() -> void {
  if(auto& sizable = state.sizable) sizable->destruct();
  mObject::destruct();
}

//

auto mToolbarItem::append(sSizable sizable) -> type& {
  if(auto& sizable = state.sizable) remove(sizable);
  state.sizable = sizable;
  sizable->setParent(this, 0);
  signal(append, sizable);
  return *this;
}

auto mToolbarItem::closable() const -> bool {
  return state.closable;
}

auto mToolbarItem::icon() const -> multiFactorImage {
  return state.icon;
}

auto mToolbarItem::movable() const -> bool {
  return state.movable;
}

auto mToolbarItem::remove() -> type& {
  if(auto Toolbar = parentToolbar()) Toolbar->remove(*this);
  return *this;
}

auto mToolbarItem::remove(sSizable sizable) -> type& {
  signal(remove, sizable);
  state.sizable.reset();
  sizable->setParent();
  return *this;
}

auto mToolbarItem::reset() -> type& {
  if(auto& sizable = state.sizable) remove(sizable);
  return *this;
}

auto mToolbarItem::selected() const -> bool {
  return state.selected;
}

auto mToolbarItem::setClosable(bool closable) -> type& {
  state.closable = closable;
  signal(setClosable, closable);
  return *this;
}

auto mToolbarItem::setEnabled(bool enabled) -> type& {
  mObject::setEnabled(enabled);
  if(auto& sizable = state.sizable) sizable->setEnabled(sizable->enabled());
  return *this;
}

auto mToolbarItem::setFont(const Font& font) -> type& {
  mObject::setFont(font);
  if(auto& sizable = state.sizable) sizable->setFont(sizable->font());
  return *this;
}

auto mToolbarItem::setIcon(const multiFactorImage& icon) -> type& {
  state.icon = icon;
  signal(setIcon, icon);
  return *this;
}

auto mToolbarItem::setMovable(bool movable) -> type& {
  state.movable = movable;
  signal(setMovable, movable);
  return *this;
}

auto mToolbarItem::setParent(mObject* parent, s32 offset) -> type& {
  if(auto& sizable = state.sizable) sizable->destruct();
  mObject::setParent(parent, offset);
  if(auto& sizable = state.sizable) sizable->setParent(this, sizable->offset());
  return *this;
}

auto mToolbarItem::setSelected() -> type& {
  if(auto parent = parentToolbar()) {
    for(auto& item : parent->state.items) item->state.selected = false;
  }
  state.selected = true;
  signal(setSelected);
  return *this;
}

auto mToolbarItem::setText(const string& text) -> type& {
  state.text = text;
  signal(setText, text);
  return *this;
}

auto mToolbarItem::setVisible(bool visible) -> type& {
  mObject::setVisible(visible);
  if(auto& sizable = state.sizable) sizable->setVisible(sizable->visible());
  return *this;
}

auto mToolbarItem::sizable() const -> Sizable {
  return state.sizable;
}

auto mToolbarItem::text() const -> string {
  return state.text;
}

#endif
