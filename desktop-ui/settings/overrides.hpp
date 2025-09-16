
// MARK: Overrides

struct Override {
  string settingName;
  string settingKey;
  string settingType;
  bool boolValue;
  string stringValue;
  s64 intValue;
  f64 realValue;
};

struct OverrideDialog : Window {
  OverrideDialog();
  auto show() -> Override;
  auto accept() -> void;
  auto cancel() -> void;
  auto updateWindow() -> void;

 VerticalLayout layout{this};
 ComboButton settingSelector{&layout, Size{80_sx, 20_sy}};
 ComboButton stringValueSelector{&layout, Size{80_sx, 20_sy}};
 TextEdit pathSelector{&layout, Size{80_sx, 20_sy}};
 HorizontalSlider numberSelector{&layout, Size{80_sx, 20_sy}};
 HorizontalLayout buttonLayout{&layout, Size{~0, ~0}};
   Button cancelButton{&buttonLayout, Size{80, 0}};
   Button acceptButton{&buttonLayout, Size{80, 0}};

private:
  Override override;
};


struct OverrideSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
  OverrideDialog overrideDialog;
  TableView overrideTable{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Button addButton{&controlLayout, Size{80, 0}};
    Button removeButton{&controlLayout, Size{80, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
};
