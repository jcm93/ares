#if defined(Hiro_ComboEdit)

@implementation CocoaComboEdit

-(id) initWith:(hiro::mComboEdit&)comboEditReference {
  if(self = [super initWithFrame:NSMakeRect(0, 0, 0, 0)]) {
    comboEdit = &comboEditReference;

    [self setTarget:self];
    [self setAction:@selector(activate:)];
  }
  return self;
}

-(IBAction) activate:(id)sender {
  //if(auto p = comboEdit->self()) p->_updateSelected([self indexOfSelectedItem]);
  comboEdit->doChange();
}

@end

namespace hiro {

auto pComboEdit::construct() -> void {
  cocoaView = cocoaComboEdit = [[CocoaComboEdit alloc] initWith:self()];
  pWidget::construct();
}

auto pComboEdit::destruct() -> void {
  [cocoaView removeFromSuperview];
}

auto pComboEdit::append(sComboEditItem item) -> void {
  [(CocoaComboEdit*)cocoaView addItemWithObjectValue:[NSString stringWithUTF8String:item->text()]];
}

auto pComboEdit::minimumSize() const -> Size {
  auto font = self().font(true);
  s32 maximumWidth = 0;
  for(auto& item : state().items) {
    maximumWidth = max(maximumWidth, pFont::size(font, item->state.text).width());
  }
  Size size = pFont::size(font, " ");
  return {maximumWidth + 36, size.height() + 6};
}

auto pComboEdit::remove(sComboEditItem item) -> void {
  [(CocoaComboEdit*)cocoaView removeItemAtIndex:item->offset()];
}

auto pComboEdit::reset() -> void {
  [(CocoaComboEdit*)cocoaView removeAllItems];
}

auto pComboEdit::setBackgroundColor(Color color) -> void {
}

auto pComboEdit::setEditable(bool editable) -> void {
  [(CocoaComboEdit*)cocoaView setEditable:YES];
}

auto pComboEdit::setForegroundColor(Color color) -> void {
}

auto pComboEdit::setFont(const Font& font) -> void {
}

auto pComboEdit::setText(const string& text) -> void {
  //do
}

auto pComboEdit::_updateText() -> void {
  //uh
}

}

#endif
