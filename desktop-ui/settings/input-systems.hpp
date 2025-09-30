
struct SystemInputSettings : VerticalLayout {
  auto construct() -> void;
  auto systemChange() -> void;
  auto portChange() -> void;
  auto deviceChange() -> void;
  auto refresh() -> void;
  auto eventContext(TableViewCell) -> void;
  auto eventChange() -> void;
  auto eventClear() -> void;
  auto eventAssign(TableViewCell, string binding) -> void;
  auto eventAssign(TableViewCell) -> void;
  auto eventInput(shared_pointer<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void;
  auto setVisible(bool visible = true) -> SystemInputSettings&;
  auto inputRefresh() -> void;
  auto inputDriverUpdate() -> bool;

  //

  HorizontalLayout indexLayout{this, Size{~0, 0}};
    ComboButton systemList{&indexLayout, Size{~0, 0}};
    ComboButton portList{&indexLayout, Size{~0, 0}};
    ComboButton deviceList{&indexLayout, Size{~0, 0}};
  TableView inputList{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Label inputDriverLabel{&controlLayout, Size{0, 0}};
    ComboButton inputDriverList{&controlLayout, Size{0, 0}};
    Label inputDefocusLabel{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusPause{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusBlock{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusAllow{&controlLayout, Size{0, 0}};
    Label assignLabel{&controlLayout, Size{~0, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
    Button assignButton{&controlLayout, Size{80, 0}};
    Button clearButton{&controlLayout, Size{80, 0}};

  Group inputDefocusGroup{&inputDefocusPause, &inputDefocusBlock, &inputDefocusAllow};

  maybe<InputNode&> activeMapping;
  u32 activeBinding = 0;
  Timer timer;
  PopupMenu menu;
};
