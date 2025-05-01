#if defined(Hiro_Toolbar)

namespace hiro {

struct pToolbarItem : pObject {
  Declare(ToolbarItem, Object)

  auto append(sSizable sizable) -> void;
  auto remove(sSizable sizable) -> void;
  auto setClosable(bool closable) -> void;
  auto setIcon(const image& icon) -> void;
  auto setMovable(bool movable) -> void;
  auto setSelected() -> void;
  auto setText(const string& text) -> void;

  CocoaToolbarItem* cocoaToolbarItem = nullptr;

  auto _parent() -> maybe<pToolbar&>;
};

}

#endif
