
// MARK: Overrides
struct OverrideSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
  TableView overrideTable{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Button addButton{&controlLayout, Size{80, 0}};
    Button removeButton{&controlLayout, Size{80, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
};

struct Override {
  string setting;
  bool boolValue;
  string stringValue;
  s64 intValue;
  f64 realValue;
};

struct OverrideDialog : Window {
  OverrideDialog();
  auto show(Override = {}) -> void;
  auto accept() -> void;
  auto cancel() -> void;
  auto updateWindow() -> void;

private:
  Override override;

  VerticalLayout layout{this};
  ComboButton settingSelector;
  ComboButton stringValueSelector;
  TextEdit pathSelector;
  HorizontalSlider numberSelector;
};
