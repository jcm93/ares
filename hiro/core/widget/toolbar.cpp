#if defined(Hiro_Toolbar)

auto mToolbar::allocate() -> pObject* {
  return new pToolbar(*this);
}

auto mToolbar::destruct() -> void {
  for(auto& item : state.items) item->destruct();
  mWidget::destruct();
}

//

auto mToolbar::append(sToolbarItem item) -> type& {
  if(state.items.empty()) item->state.selected = true;
  state.items.push_back(item);
  item->setParent(this, itemCount() - 1);
  signal(append, item);
  return *this;
}

auto mToolbar::setWindow(sWindow window) -> void {
  signal(setWindow, window);
}

auto mToolbar::doChange() const -> void {
  if(state.onChange) return state.onChange();
}

auto mToolbar::doClose(sToolbarItem item) const -> void {
  if(state.onClose) return state.onClose(item);
}

auto mToolbar::doMove(sToolbarItem from, sToolbarItem to) const -> void {
  if(state.onMove) return state.onMove(from, to);
}

auto mToolbar::item(unsigned position) const -> ToolbarItem {
  if(position < state.items.size()) return state.items[position];
  return {};
}

auto mToolbar::itemCount() const -> unsigned {
  return state.items.size();
}

auto mToolbar::items() const -> std::vector<ToolbarItem> {
  std::vector<ToolbarItem> items;
  for(auto& item : state.items) items.push_back(item);
  return items;
}

auto mToolbar::navigation() const -> Navigation {
  return state.navigation;
}

auto mToolbar::onChange(const function<void ()>& callback) -> type& {
  state.onChange = callback;
  return *this;
}

auto mToolbar::onClose(const function<void (ToolbarItem)>& callback) -> type& {
  state.onClose = callback;
  return *this;
}

auto mToolbar::onMove(const function<void (ToolbarItem, ToolbarItem)>& callback) -> type& {
  state.onMove = callback;
  return *this;
}

auto mToolbar::onSelect(string identifier) -> type& {
  for(auto n : range(0, itemCount())) {
    state.items[n]->state.selected = false;
    if(state.items[n]->state.text == identifier) {
      state.items[n]->state.selected = true;
    }
  }
  return *this;
}

auto mToolbar::remove(sToolbarItem item) -> type& {
  auto offset = item->offset();
  item->setParent();
  signal(remove, item);
  state.items.erase(state.items.begin() + item->offset());
  for(auto n : range(offset, itemCount())) {
    state.items[n]->adjustOffset(-1);
  }
  return *this;
}

auto mToolbar::reset() -> type& {
  while(!state.items.empty()) remove(state.items.back());
  return *this;
}

auto mToolbar::selected() const -> ToolbarItem {
  for(auto& item : state.items) {
    if(item->selected()) return item;
  }
  return {};
}

auto mToolbar::setEnabled(bool enabled) -> type& {
  mWidget::setEnabled(enabled);
  for(auto& item : state.items) item->setEnabled(item->enabled());
  return *this;
}

auto mToolbar::setFont(const Font& font) -> type& {
  mWidget::setFont(font);
  for(auto& item : state.items) item->setFont(item->font());
  return *this;
}

auto mToolbar::setNavigation(Navigation navigation) -> type& {
  state.navigation = navigation;
  signal(setNavigation, navigation);
  return *this;
}

auto mToolbar::setParent(mObject* parent, s32 offset) -> type& {
  for(auto& item : state.items | std::views::reverse) item->destruct();
  mObject::setParent(parent, offset);
  for(auto& item : state.items) item->setParent(this, item->offset());
  return *this;
}

auto mToolbar::setVisible(bool visible) -> type& {
  mWidget::setVisible(visible);
  for(auto& item : state.items) item->setVisible(item->visible());
  return *this;
}

#endif
