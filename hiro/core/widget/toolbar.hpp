#if defined(Hiro_Toolbar)
struct mToolbar : mWidget {
  Declare(Toolbar)
  using mObject::remove;
  friend struct mToolbarItem;

  auto append(sToolbarItem item) -> type&;
  auto doChange() const -> void;
  auto doClose(sToolbarItem item) const -> void;
  auto doMove(sToolbarItem from, sToolbarItem to) const -> void;
  auto item(uint position) const -> ToolbarItem;
  auto itemCount() const -> uint;
  auto items() const -> vector<ToolbarItem>;
  auto navigation() const -> Navigation;
  auto onChange(const function<void ()>& callback = {}) -> type&;
  auto onClose(const function<void (ToolbarItem)>& callback = {}) -> type&;
  auto onMove(const function<void (ToolbarItem, ToolbarItem)>& callback = {}) -> type&;
  auto remove(sToolbarItem item) -> type&;
  auto reset() -> type& override;
  auto selected() const -> ToolbarItem;
  auto setEnabled(bool enabled = true) -> type& override;
  auto setFont(const Font& font = {}) -> type& override;
  auto setNavigation(Navigation navigation = Navigation::Top) -> type&;
  auto setParent(mObject* object = nullptr, s32 offset = -1) -> type& override;
  auto setVisible(bool visible = true) -> type& override;

//private:
  struct State {
    vector<sToolbarItem> items;
    Navigation navigation = Navigation::Top;
    function<void ()> onChange;
    function<void (ToolbarItem)> onClose;
    function<void (ToolbarItem, ToolbarItem)> onMove;
  } state;

  auto destruct() -> void override;
};
#endif
