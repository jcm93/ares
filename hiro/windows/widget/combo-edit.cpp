#if defined(Hiro_ComboEdit)

namespace hiro {

auto pComboEdit::construct() -> void {
  hwnd = CreateWindow(
    L"COMBOBOX", L"",
    WS_CHILD | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWN	 | CBS_HASSTRINGS,
    0, 0, 0, 0,
    _parentHandle(), nullptr, GetModuleHandle(0), 0
  );
  pWidget::construct();
  for(auto& item : state().items) append(item);
}

auto pComboEdit::destruct() -> void {
  DestroyWindow(hwnd);
}

auto pComboEdit::append(sComboEditItem item) -> void {
  lock();
  SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(wchar_t*)utf16_t(item->state.text));
  if(item->state.selected) SendMessage(hwnd, CB_SETCURSEL, item->offset(), 0);
  if(SendMessage(hwnd, CB_GETCURSEL, 0, 0) == CB_ERR) item->setSelected();
  unlock();
}

auto pComboEdit::minimumSize() const -> Size {
  s32 width = 0;
  for(auto& item : state().items) {
    width = max(width, pFont::size(hfont, item->state.text).width());
  }
  return {width + 24_sx, pFont::size(hfont, " ").height() + 10_sy};
}

auto pComboEdit::remove(sComboEditItem item) -> void {
  lock();
  SendMessage(hwnd, CB_DELETESTRING, item->offset(), 0);
  if(item->state.selected) SendMessage(hwnd, CB_SETCURSEL, 0, 0);
  unlock();
}

auto pComboEdit::reset() -> void {
  SendMessage(hwnd, CB_RESETCONTENT, 0, 0);
}

auto pComboEdit::setBackgroundColor(Color color) -> void {
}

auto pComboEdit::setEditable(bool editable) -> void {
}

auto pComboEdit::setForegroundColor(Color color) -> void {
}

auto pComboEdit::setFont(const Font& font) -> void {
}

auto pComboEdit::setText(const string& text) -> void {
}

auto pComboEdit::_updateText() -> void {
}

//Windows overrides the height parameter for a ComboEdit's SetWindowPos to be the drop-down list height.
//the canonical way to set the actual height is through CB_SETITEMHEIGHT. However, doing so is bugged.
//the ComboEdit will end up not being painted for ~500ms after calling ShowWindow(hwnd, SW_NORMAL) on it.
//thus, implementing windows that use multiple pages of controls via toggling visibility will flicker heavily.
//as a result, the best we can do is center the actual widget within the requested space.
auto pComboEdit::setGeometry(Geometry geometry) -> void {
  //since the ComboEdit has a fixed height, it will always be the same, even before calling setGeometry() once.
  RECT rc;
  GetWindowRect(hwnd, &rc);
  geometry.setY(geometry.y() + (geometry.height() - (rc.bottom - rc.top)));
  pWidget::setGeometry({geometry.x(), geometry.y(), geometry.width(), 1});
}

auto pComboEdit::onChange() -> void {
  s32 offset = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
  if(offset == CB_ERR) return;
  for(auto& item : state().items) item->state.selected = false;
  if(auto item = self().item(offset)) item->setSelected();
  self().doChange();
}

}

#endif

