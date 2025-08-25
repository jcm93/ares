#if defined(Hiro_ComboEdit)

@interface CocoaComboEdit : NSComboBox {
@public
  hiro::mComboEdit* comboEdit;
}
-(id) initWith:(hiro::mComboEdit&)comboEdit;
-(IBAction) activate:(id)sender;
@end

namespace hiro {

struct pComboEdit : pWidget {
  Declare(ComboEdit, Widget)

  auto append(sComboEditItem item) -> void;
  auto minimumSize() const -> Size override;
  auto remove(sComboEditItem item) -> void;
  auto reset() -> void override;
  auto setBackgroundColor(Color color) -> void;
  auto setEditable(bool editable) -> void;
  auto setForegroundColor(Color color) -> void;
  auto setFont(const Font& font) -> void override;
  auto setText(const string& text) -> void;

  auto _updateText() -> void;

  CocoaComboEdit* cocoaComboEdit = nullptr;
};

}

#endif

