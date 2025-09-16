
struct SystemInputSettings : VerticalLayout {
  auto construct() -> void;
  auto systemChange(std::shared_ptr<Emulator> emulator) -> void;
  auto portChange() -> void;
  auto deviceChange() -> void;
  auto refresh() -> void;
  auto eventContext(TableViewCell) -> void;
  auto eventChange() -> void;
  auto eventClear() -> void;
  auto eventAssign(TableViewCell, string binding) -> void;
  auto eventAssign(TableViewCell) -> void;
  auto eventInput(std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void;
  auto setVisible(bool visible = true) -> SystemInputSettings&;
  auto inputRefresh() -> void;
  auto inputDriverUpdate() -> bool;

  std::shared_ptr<Emulator> emulator;

  //

  HorizontalLayout indexLayout{this, Size{~0, 0}};
  ComboButton portList{&indexLayout, Size{~0, 0}};
  ComboButton deviceList{&indexLayout, Size{~0, 0}};
  TableView inputList{this, Size{~0, ~0}};

  maybe<InputNode&> activeMapping;
  u32 activeBinding = 0;
  Timer timer;
  PopupMenu menu;

  Group mappingsMenuItemsGroup;

  //fixme-before-merge: everything below this point is cursed beyond comprehension
  string analogInputs[10] = {
    "Pad/L.Trigger",
    "Pad/R.Trigger",
    "Pad/LStick.Up",
    "Pad/LStick.Down",
    "Pad/LStick.Left",
    "Pad/LStick.Right",
    "Pad/RStick.Up",
    "Pad/RStick.Down",
    "Pad/RStick.Left",
    "Pad/RStick.Right"
  };

  string digitalInputs[33] = {
    "Mouse/Left",
    "Mouse/Middle",
    "Mouse/Right",
    "Mouse/Extra",
    "Pad/One",
    "Pad/Two",
    "Pad/Three",
    "Pad/Four",
    "Pad/Five",
    "Pad/Six",
    "Pad/Seven",
    "Pad/Eight",
    "Pad/Nine",
    "Pad/Zero",
    "Pad/Star",
    "Pad/Clear",
    "Pad/Pound",
    "Pad/Point",
    "Pad/End",
    "Pad/LStick.Click",
    "Pad/RStick.Click",
    "Pad/Up",
    "Pad/Down",
    "Pad/Left",
    "Pad/Right",
    "Pad/Select",
    "Pad/Start",
    "Pad/South",
    "Pad/East",
    "Pad/West",
    "Pad/North",
    "Pad/L.Bumper",
    "Pad/R.Bumper",
  };

  string relativeInputs[2] = {
    "Mouse/X",
    "Mouse/Y"
  };

  map<string, InputAnalog> cursedAnalogMap;
  map<string, InputDigital> cursedDigitalMap;
  map<string, InputRelative> cursedRelativeMap;
  map<InputAnalog, string> otherCursedAnalogMap;
  map<InputDigital, string> otherCursedDigitalMap;
  map<InputRelative, string> otherCursedRelativeMap;

  auto veryBadFunction() -> void {
    // MARK: analog
    cursedAnalogMap.insert("VirtualPad1/Pad/L.Trigger", virtualPorts[0].pad.l_trigger);
    cursedAnalogMap.insert("VirtualPad1/Pad/R.Trigger", virtualPorts[0].pad.r_trigger);
    cursedAnalogMap.insert("VirtualPad1/Pad/LStick.Up", virtualPorts[0].pad.lstick_up);
    cursedAnalogMap.insert("VirtualPad1/Pad/LStick.Down", virtualPorts[0].pad.lstick_down);
    cursedAnalogMap.insert("VirtualPad1/Pad/LStick.Left", virtualPorts[0].pad.lstick_left);
    cursedAnalogMap.insert("VirtualPad1/Pad/LStick.Right", virtualPorts[0].pad.lstick_right);
    cursedAnalogMap.insert("VirtualPad1/Pad/RStick.Up", virtualPorts[0].pad.rstick_up);
    cursedAnalogMap.insert("VirtualPad1/Pad/RStick.Down", virtualPorts[0].pad.rstick_down);
    cursedAnalogMap.insert("VirtualPad1/Pad/RStick.Left", virtualPorts[0].pad.rstick_left);
    cursedAnalogMap.insert("VirtualPad1/Pad/RStick.Right", virtualPorts[0].pad.rstick_right);

    cursedAnalogMap.insert("VirtualPad2/Pad/L.Trigger", virtualPorts[1].pad.l_trigger);
    cursedAnalogMap.insert("VirtualPad2/Pad/R.Trigger", virtualPorts[1].pad.r_trigger);
    cursedAnalogMap.insert("VirtualPad2/Pad/LStick.Up", virtualPorts[1].pad.lstick_up);
    cursedAnalogMap.insert("VirtualPad2/Pad/LStick.Down", virtualPorts[1].pad.lstick_down);
    cursedAnalogMap.insert("VirtualPad2/Pad/LStick.Left", virtualPorts[1].pad.lstick_left);
    cursedAnalogMap.insert("VirtualPad2/Pad/LStick.Right", virtualPorts[1].pad.lstick_right);
    cursedAnalogMap.insert("VirtualPad2/Pad/RStick.Up", virtualPorts[1].pad.rstick_up);
    cursedAnalogMap.insert("VirtualPad2/Pad/RStick.Down", virtualPorts[1].pad.rstick_down);
    cursedAnalogMap.insert("VirtualPad2/Pad/RStick.Left", virtualPorts[1].pad.rstick_left);
    cursedAnalogMap.insert("VirtualPad2/Pad/RStick.Right", virtualPorts[1].pad.rstick_right);

    cursedAnalogMap.insert("VirtualPad3/Pad/L.Trigger", virtualPorts[2].pad.l_trigger);
    cursedAnalogMap.insert("VirtualPad3/Pad/R.Trigger", virtualPorts[2].pad.r_trigger);
    cursedAnalogMap.insert("VirtualPad3/Pad/LStick.Up", virtualPorts[2].pad.lstick_up);
    cursedAnalogMap.insert("VirtualPad3/Pad/LStick.Down", virtualPorts[2].pad.lstick_down);
    cursedAnalogMap.insert("VirtualPad3/Pad/LStick.Left", virtualPorts[2].pad.lstick_left);
    cursedAnalogMap.insert("VirtualPad3/Pad/LStick.Right", virtualPorts[2].pad.lstick_right);
    cursedAnalogMap.insert("VirtualPad3/Pad/RStick.Up", virtualPorts[2].pad.rstick_up);
    cursedAnalogMap.insert("VirtualPad3/Pad/RStick.Down", virtualPorts[2].pad.rstick_down);
    cursedAnalogMap.insert("VirtualPad3/Pad/RStick.Left", virtualPorts[2].pad.rstick_left);
    cursedAnalogMap.insert("VirtualPad3/Pad/RStick.Right", virtualPorts[2].pad.rstick_right);

    cursedAnalogMap.insert("VirtualPad4/Pad/L.Trigger", virtualPorts[3].pad.l_trigger);
    cursedAnalogMap.insert("VirtualPad4/Pad/R.Trigger", virtualPorts[3].pad.r_trigger);
    cursedAnalogMap.insert("VirtualPad4/Pad/LStick.Up", virtualPorts[3].pad.lstick_up);
    cursedAnalogMap.insert("VirtualPad4/Pad/LStick.Down", virtualPorts[3].pad.lstick_down);
    cursedAnalogMap.insert("VirtualPad4/Pad/LStick.Left", virtualPorts[3].pad.lstick_left);
    cursedAnalogMap.insert("VirtualPad4/Pad/LStick.Right", virtualPorts[3].pad.lstick_right);
    cursedAnalogMap.insert("VirtualPad4/Pad/RStick.Up", virtualPorts[3].pad.rstick_up);
    cursedAnalogMap.insert("VirtualPad4/Pad/RStick.Down", virtualPorts[3].pad.rstick_down);
    cursedAnalogMap.insert("VirtualPad4/Pad/RStick.Left", virtualPorts[3].pad.rstick_left);
    cursedAnalogMap.insert("VirtualPad4/Pad/RStick.Right", virtualPorts[3].pad.rstick_right);

    cursedAnalogMap.insert("VirtualPad5/Pad/L.Trigger", virtualPorts[4].pad.l_trigger);
    cursedAnalogMap.insert("VirtualPad5/Pad/R.Trigger", virtualPorts[4].pad.r_trigger);
    cursedAnalogMap.insert("VirtualPad5/Pad/LStick.Up", virtualPorts[4].pad.lstick_up);
    cursedAnalogMap.insert("VirtualPad5/Pad/LStick.Down", virtualPorts[4].pad.lstick_down);
    cursedAnalogMap.insert("VirtualPad5/Pad/LStick.Left", virtualPorts[4].pad.lstick_left);
    cursedAnalogMap.insert("VirtualPad5/Pad/LStick.Right", virtualPorts[4].pad.lstick_right);
    cursedAnalogMap.insert("VirtualPad5/Pad/RStick.Up", virtualPorts[4].pad.rstick_up);
    cursedAnalogMap.insert("VirtualPad5/Pad/RStick.Down", virtualPorts[4].pad.rstick_down);
    cursedAnalogMap.insert("VirtualPad5/Pad/RStick.Left", virtualPorts[4].pad.rstick_left);
    cursedAnalogMap.insert("VirtualPad5/Pad/RStick.Right", virtualPorts[4].pad.rstick_right);

    // MARK: digital

    cursedDigitalMap.insert("VirtualPad1/Mouse/Left", virtualPorts[0].mouse.left);
    cursedDigitalMap.insert("VirtualPad1/Mouse/Middle", virtualPorts[0].mouse.middle);
    cursedDigitalMap.insert("VirtualPad1/Mouse/Right", virtualPorts[0].mouse.right);
    cursedDigitalMap.insert("VirtualPad1/Mouse/Extra", virtualPorts[0].mouse.extra);
    cursedDigitalMap.insert("VirtualPad1/Pad/One", virtualPorts[0].pad.one);
    cursedDigitalMap.insert("VirtualPad1/Pad/Two", virtualPorts[0].pad.two);
    cursedDigitalMap.insert("VirtualPad1/Pad/Three", virtualPorts[0].pad.three);
    cursedDigitalMap.insert("VirtualPad1/Pad/Four", virtualPorts[0].pad.four);
    cursedDigitalMap.insert("VirtualPad1/Pad/Five", virtualPorts[0].pad.five);
    cursedDigitalMap.insert("VirtualPad1/Pad/Six", virtualPorts[0].pad.six);
    cursedDigitalMap.insert("VirtualPad1/Pad/Seven", virtualPorts[0].pad.seven);
    cursedDigitalMap.insert("VirtualPad1/Pad/Eight", virtualPorts[0].pad.eight);
    cursedDigitalMap.insert("VirtualPad1/Pad/Nine", virtualPorts[0].pad.nine);
    cursedDigitalMap.insert("VirtualPad1/Pad/Zero", virtualPorts[0].pad.zero);
    cursedDigitalMap.insert("VirtualPad1/Pad/Star", virtualPorts[0].pad.star);
    cursedDigitalMap.insert("VirtualPad1/Pad/Clear", virtualPorts[0].pad.clear);
    cursedDigitalMap.insert("VirtualPad1/Pad/Pound", virtualPorts[0].pad.pound);
    cursedDigitalMap.insert("VirtualPad1/Pad/Point", virtualPorts[0].pad.point);
    cursedDigitalMap.insert("VirtualPad1/Pad/End", virtualPorts[0].pad.end);
    cursedDigitalMap.insert("VirtualPad1/Pad/LStick.Click", virtualPorts[0].pad.lstick_click);
    cursedDigitalMap.insert("VirtualPad1/Pad/RStick.Click", virtualPorts[0].pad.rstick_click);
    cursedDigitalMap.insert("VirtualPad1/Pad/Up", virtualPorts[0].pad.up);
    cursedDigitalMap.insert("VirtualPad1/Pad/Down", virtualPorts[0].pad.down);
    cursedDigitalMap.insert("VirtualPad1/Pad/Left", virtualPorts[0].pad.left);
    cursedDigitalMap.insert("VirtualPad1/Pad/Right", virtualPorts[0].pad.right);
    cursedDigitalMap.insert("VirtualPad1/Pad/Select", virtualPorts[0].pad.select);
    cursedDigitalMap.insert("VirtualPad1/Pad/Start", virtualPorts[0].pad.start);
    cursedDigitalMap.insert("VirtualPad1/Pad/South", virtualPorts[0].pad.south);
    cursedDigitalMap.insert("VirtualPad1/Pad/East", virtualPorts[0].pad.east);
    cursedDigitalMap.insert("VirtualPad1/Pad/West", virtualPorts[0].pad.west);
    cursedDigitalMap.insert("VirtualPad1/Pad/North", virtualPorts[0].pad.north);
    cursedDigitalMap.insert("VirtualPad1/Pad/L.Bumper", virtualPorts[0].pad.l_bumper);
    cursedDigitalMap.insert("VirtualPad1/Pad/R.Bumper", virtualPorts[0].pad.r_bumper);

    cursedDigitalMap.insert("VirtualPad2/Mouse/Left", virtualPorts[1].mouse.left);
    cursedDigitalMap.insert("VirtualPad2/Mouse/Middle", virtualPorts[1].mouse.middle);
    cursedDigitalMap.insert("VirtualPad2/Mouse/Right", virtualPorts[1].mouse.right);
    cursedDigitalMap.insert("VirtualPad2/Mouse/Extra", virtualPorts[1].mouse.extra);
    cursedDigitalMap.insert("VirtualPad2/Pad/One", virtualPorts[1].pad.one);
    cursedDigitalMap.insert("VirtualPad2/Pad/Two", virtualPorts[1].pad.two);
    cursedDigitalMap.insert("VirtualPad2/Pad/Three", virtualPorts[1].pad.three);
    cursedDigitalMap.insert("VirtualPad2/Pad/Four", virtualPorts[1].pad.four);
    cursedDigitalMap.insert("VirtualPad2/Pad/Five", virtualPorts[1].pad.five);
    cursedDigitalMap.insert("VirtualPad2/Pad/Six", virtualPorts[1].pad.six);
    cursedDigitalMap.insert("VirtualPad2/Pad/Seven", virtualPorts[1].pad.seven);
    cursedDigitalMap.insert("VirtualPad2/Pad/Eight", virtualPorts[1].pad.eight);
    cursedDigitalMap.insert("VirtualPad2/Pad/Nine", virtualPorts[1].pad.nine);
    cursedDigitalMap.insert("VirtualPad2/Pad/Zero", virtualPorts[1].pad.zero);
    cursedDigitalMap.insert("VirtualPad2/Pad/Star", virtualPorts[1].pad.star);
    cursedDigitalMap.insert("VirtualPad2/Pad/Clear", virtualPorts[1].pad.clear);
    cursedDigitalMap.insert("VirtualPad2/Pad/Pound", virtualPorts[1].pad.pound);
    cursedDigitalMap.insert("VirtualPad2/Pad/Point", virtualPorts[1].pad.point);
    cursedDigitalMap.insert("VirtualPad2/Pad/End", virtualPorts[1].pad.end);
    cursedDigitalMap.insert("VirtualPad2/Pad/LStick.Click", virtualPorts[1].pad.lstick_click);
    cursedDigitalMap.insert("VirtualPad2/Pad/RStick.Click", virtualPorts[1].pad.rstick_click);
    cursedDigitalMap.insert("VirtualPad2/Pad/Up", virtualPorts[1].pad.up);
    cursedDigitalMap.insert("VirtualPad2/Pad/Down", virtualPorts[1].pad.down);
    cursedDigitalMap.insert("VirtualPad2/Pad/Left", virtualPorts[1].pad.left);
    cursedDigitalMap.insert("VirtualPad2/Pad/Right", virtualPorts[1].pad.right);
    cursedDigitalMap.insert("VirtualPad2/Pad/Select", virtualPorts[1].pad.select);
    cursedDigitalMap.insert("VirtualPad2/Pad/Start", virtualPorts[1].pad.start);
    cursedDigitalMap.insert("VirtualPad2/Pad/South", virtualPorts[1].pad.south);
    cursedDigitalMap.insert("VirtualPad2/Pad/East", virtualPorts[1].pad.east);
    cursedDigitalMap.insert("VirtualPad2/Pad/West", virtualPorts[1].pad.west);
    cursedDigitalMap.insert("VirtualPad2/Pad/North", virtualPorts[1].pad.north);
    cursedDigitalMap.insert("VirtualPad2/Pad/L.Bumper", virtualPorts[1].pad.l_bumper);
    cursedDigitalMap.insert("VirtualPad2/Pad/R.Bumper", virtualPorts[1].pad.r_bumper);

    cursedDigitalMap.insert("VirtualPad3/Mouse/Left", virtualPorts[2].mouse.left);
    cursedDigitalMap.insert("VirtualPad3/Mouse/Middle", virtualPorts[2].mouse.middle);
    cursedDigitalMap.insert("VirtualPad3/Mouse/Right", virtualPorts[2].mouse.right);
    cursedDigitalMap.insert("VirtualPad3/Mouse/Extra", virtualPorts[2].mouse.extra);
    cursedDigitalMap.insert("VirtualPad3/Pad/One", virtualPorts[2].pad.one);
    cursedDigitalMap.insert("VirtualPad3/Pad/Two", virtualPorts[2].pad.two);
    cursedDigitalMap.insert("VirtualPad3/Pad/Three", virtualPorts[2].pad.three);
    cursedDigitalMap.insert("VirtualPad3/Pad/Four", virtualPorts[2].pad.four);
    cursedDigitalMap.insert("VirtualPad3/Pad/Five", virtualPorts[2].pad.five);
    cursedDigitalMap.insert("VirtualPad3/Pad/Six", virtualPorts[2].pad.six);
    cursedDigitalMap.insert("VirtualPad3/Pad/Seven", virtualPorts[2].pad.seven);
    cursedDigitalMap.insert("VirtualPad3/Pad/Eight", virtualPorts[2].pad.eight);
    cursedDigitalMap.insert("VirtualPad3/Pad/Nine", virtualPorts[2].pad.nine);
    cursedDigitalMap.insert("VirtualPad3/Pad/Zero", virtualPorts[2].pad.zero);
    cursedDigitalMap.insert("VirtualPad3/Pad/Star", virtualPorts[2].pad.star);
    cursedDigitalMap.insert("VirtualPad3/Pad/Clear", virtualPorts[2].pad.clear);
    cursedDigitalMap.insert("VirtualPad3/Pad/Pound", virtualPorts[2].pad.pound);
    cursedDigitalMap.insert("VirtualPad3/Pad/Point", virtualPorts[2].pad.point);
    cursedDigitalMap.insert("VirtualPad3/Pad/End", virtualPorts[2].pad.end);
    cursedDigitalMap.insert("VirtualPad3/Pad/LStick.Click", virtualPorts[2].pad.lstick_click);
    cursedDigitalMap.insert("VirtualPad3/Pad/RStick.Click", virtualPorts[2].pad.rstick_click);
    cursedDigitalMap.insert("VirtualPad3/Pad/Up", virtualPorts[2].pad.up);
    cursedDigitalMap.insert("VirtualPad3/Pad/Down", virtualPorts[2].pad.down);
    cursedDigitalMap.insert("VirtualPad3/Pad/Left", virtualPorts[2].pad.left);
    cursedDigitalMap.insert("VirtualPad3/Pad/Right", virtualPorts[2].pad.right);
    cursedDigitalMap.insert("VirtualPad3/Pad/Select", virtualPorts[2].pad.select);
    cursedDigitalMap.insert("VirtualPad3/Pad/Start", virtualPorts[2].pad.start);
    cursedDigitalMap.insert("VirtualPad3/Pad/South", virtualPorts[2].pad.south);
    cursedDigitalMap.insert("VirtualPad3/Pad/East", virtualPorts[2].pad.east);
    cursedDigitalMap.insert("VirtualPad3/Pad/West", virtualPorts[2].pad.west);
    cursedDigitalMap.insert("VirtualPad3/Pad/North", virtualPorts[2].pad.north);
    cursedDigitalMap.insert("VirtualPad3/Pad/L.Bumper", virtualPorts[2].pad.l_bumper);
    cursedDigitalMap.insert("VirtualPad3/Pad/R.Bumper", virtualPorts[2].pad.r_bumper);

    cursedDigitalMap.insert("VirtualPad4/Mouse/Left", virtualPorts[3].mouse.left);
    cursedDigitalMap.insert("VirtualPad4/Mouse/Middle", virtualPorts[3].mouse.middle);
    cursedDigitalMap.insert("VirtualPad4/Mouse/Right", virtualPorts[3].mouse.right);
    cursedDigitalMap.insert("VirtualPad4/Mouse/Extra", virtualPorts[3].mouse.extra);
    cursedDigitalMap.insert("VirtualPad4/Pad/One", virtualPorts[3].pad.one);
    cursedDigitalMap.insert("VirtualPad4/Pad/Two", virtualPorts[3].pad.two);
    cursedDigitalMap.insert("VirtualPad4/Pad/Three", virtualPorts[3].pad.three);
    cursedDigitalMap.insert("VirtualPad4/Pad/Four", virtualPorts[3].pad.four);
    cursedDigitalMap.insert("VirtualPad4/Pad/Five", virtualPorts[3].pad.five);
    cursedDigitalMap.insert("VirtualPad4/Pad/Six", virtualPorts[3].pad.six);
    cursedDigitalMap.insert("VirtualPad4/Pad/Seven", virtualPorts[3].pad.seven);
    cursedDigitalMap.insert("VirtualPad4/Pad/Eight", virtualPorts[3].pad.eight);
    cursedDigitalMap.insert("VirtualPad4/Pad/Nine", virtualPorts[3].pad.nine);
    cursedDigitalMap.insert("VirtualPad4/Pad/Zero", virtualPorts[3].pad.zero);
    cursedDigitalMap.insert("VirtualPad4/Pad/Star", virtualPorts[3].pad.star);
    cursedDigitalMap.insert("VirtualPad4/Pad/Clear", virtualPorts[3].pad.clear);
    cursedDigitalMap.insert("VirtualPad4/Pad/Pound", virtualPorts[3].pad.pound);
    cursedDigitalMap.insert("VirtualPad4/Pad/Point", virtualPorts[3].pad.point);
    cursedDigitalMap.insert("VirtualPad4/Pad/End", virtualPorts[3].pad.end);
    cursedDigitalMap.insert("VirtualPad4/Pad/LStick.Click", virtualPorts[3].pad.lstick_click);
    cursedDigitalMap.insert("VirtualPad4/Pad/RStick.Click", virtualPorts[3].pad.rstick_click);
    cursedDigitalMap.insert("VirtualPad4/Pad/Up", virtualPorts[3].pad.up);
    cursedDigitalMap.insert("VirtualPad4/Pad/Down", virtualPorts[3].pad.down);
    cursedDigitalMap.insert("VirtualPad4/Pad/Left", virtualPorts[3].pad.left);
    cursedDigitalMap.insert("VirtualPad4/Pad/Right", virtualPorts[3].pad.right);
    cursedDigitalMap.insert("VirtualPad4/Pad/Select", virtualPorts[3].pad.select);
    cursedDigitalMap.insert("VirtualPad4/Pad/Start", virtualPorts[3].pad.start);
    cursedDigitalMap.insert("VirtualPad4/Pad/South", virtualPorts[3].pad.south);
    cursedDigitalMap.insert("VirtualPad4/Pad/East", virtualPorts[3].pad.east);
    cursedDigitalMap.insert("VirtualPad4/Pad/West", virtualPorts[3].pad.west);
    cursedDigitalMap.insert("VirtualPad4/Pad/North", virtualPorts[3].pad.north);
    cursedDigitalMap.insert("VirtualPad4/Pad/L.Bumper", virtualPorts[3].pad.l_bumper);
    cursedDigitalMap.insert("VirtualPad4/Pad/R.Bumper", virtualPorts[3].pad.r_bumper);

    cursedDigitalMap.insert("VirtualPad5/Mouse/Left", virtualPorts[4].mouse.left);
    cursedDigitalMap.insert("VirtualPad5/Mouse/Middle", virtualPorts[4].mouse.middle);
    cursedDigitalMap.insert("VirtualPad5/Mouse/Right", virtualPorts[4].mouse.right);
    cursedDigitalMap.insert("VirtualPad5/Mouse/Extra", virtualPorts[4].mouse.extra);
    cursedDigitalMap.insert("VirtualPad5/Pad/One", virtualPorts[4].pad.one);
    cursedDigitalMap.insert("VirtualPad5/Pad/Two", virtualPorts[4].pad.two);
    cursedDigitalMap.insert("VirtualPad5/Pad/Three", virtualPorts[4].pad.three);
    cursedDigitalMap.insert("VirtualPad5/Pad/Four", virtualPorts[4].pad.four);
    cursedDigitalMap.insert("VirtualPad5/Pad/Five", virtualPorts[4].pad.five);
    cursedDigitalMap.insert("VirtualPad5/Pad/Six", virtualPorts[4].pad.six);
    cursedDigitalMap.insert("VirtualPad5/Pad/Seven", virtualPorts[4].pad.seven);
    cursedDigitalMap.insert("VirtualPad5/Pad/Eight", virtualPorts[4].pad.eight);
    cursedDigitalMap.insert("VirtualPad5/Pad/Nine", virtualPorts[4].pad.nine);
    cursedDigitalMap.insert("VirtualPad5/Pad/Zero", virtualPorts[4].pad.zero);
    cursedDigitalMap.insert("VirtualPad5/Pad/Star", virtualPorts[4].pad.star);
    cursedDigitalMap.insert("VirtualPad5/Pad/Clear", virtualPorts[4].pad.clear);
    cursedDigitalMap.insert("VirtualPad5/Pad/Pound", virtualPorts[4].pad.pound);
    cursedDigitalMap.insert("VirtualPad5/Pad/Point", virtualPorts[4].pad.point);
    cursedDigitalMap.insert("VirtualPad5/Pad/End", virtualPorts[4].pad.end);
    cursedDigitalMap.insert("VirtualPad5/Pad/LStick.Click", virtualPorts[4].pad.lstick_click);
    cursedDigitalMap.insert("VirtualPad5/Pad/RStick.Click", virtualPorts[4].pad.rstick_click);
    cursedDigitalMap.insert("VirtualPad5/Pad/Up", virtualPorts[4].pad.up);
    cursedDigitalMap.insert("VirtualPad5/Pad/Down", virtualPorts[4].pad.down);
    cursedDigitalMap.insert("VirtualPad5/Pad/Left", virtualPorts[4].pad.left);
    cursedDigitalMap.insert("VirtualPad5/Pad/Right", virtualPorts[4].pad.right);
    cursedDigitalMap.insert("VirtualPad5/Pad/Select", virtualPorts[4].pad.select);
    cursedDigitalMap.insert("VirtualPad5/Pad/Start", virtualPorts[4].pad.start);
    cursedDigitalMap.insert("VirtualPad5/Pad/South", virtualPorts[4].pad.south);
    cursedDigitalMap.insert("VirtualPad5/Pad/East", virtualPorts[4].pad.east);
    cursedDigitalMap.insert("VirtualPad5/Pad/West", virtualPorts[4].pad.west);
    cursedDigitalMap.insert("VirtualPad5/Pad/North", virtualPorts[4].pad.north);
    cursedDigitalMap.insert("VirtualPad5/Pad/L.Bumper", virtualPorts[4].pad.l_bumper);
    cursedDigitalMap.insert("VirtualPad5/Pad/R.Bumper", virtualPorts[4].pad.r_bumper);

    // MARK: relative

    cursedRelativeMap.insert("VirtualPad1/Mouse/X", virtualPorts[0].mouse.x);
    cursedRelativeMap.insert("VirtualPad1/Mouse/Y", virtualPorts[0].mouse.y);

    cursedRelativeMap.insert("VirtualPad2/Mouse/X", virtualPorts[1].mouse.x);
    cursedRelativeMap.insert("VirtualPad2/Mouse/Y", virtualPorts[1].mouse.y);

    cursedRelativeMap.insert("VirtualPad3/Mouse/X", virtualPorts[2].mouse.x);
    cursedRelativeMap.insert("VirtualPad3/Mouse/Y", virtualPorts[2].mouse.y);

    cursedRelativeMap.insert("VirtualPad4/Mouse/X", virtualPorts[3].mouse.x);
    cursedRelativeMap.insert("VirtualPad4/Mouse/Y", virtualPorts[3].mouse.y);

    cursedRelativeMap.insert("VirtualPad5/Mouse/X", virtualPorts[4].mouse.x);
    cursedRelativeMap.insert("VirtualPad5/Mouse/Y", virtualPorts[4].mouse.y);
  }

  /*auto otherVeryBadFunction() -> void {
    // MARK: analog
    otherCursedAnalogMap.insert(virtualPorts[0].pad.l_trigger, "VirtualPad1/Pad/L.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.r_trigger, "VirtualPad1/Pad/R.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.lstick_up, "VirtualPad1/Pad/LStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.lstick_down, "VirtualPad1/Pad/LStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.lstick_left, "VirtualPad1/Pad/LStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.lstick_right, "VirtualPad1/Pad/LStick.Right");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.rstick_up, "VirtualPad1/Pad/RStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.rstick_down, "VirtualPad1/Pad/RStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.rstick_left, "VirtualPad1/Pad/RStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[0].pad.rstick_right, "VirtualPad1/Pad/RStick.Right");

    otherCursedAnalogMap.insert(virtualPorts[1].pad.l_trigger, "VirtualPad2/Pad/L.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.r_trigger, "VirtualPad2/Pad/R.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.lstick_up, "VirtualPad2/Pad/LStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.lstick_down, "VirtualPad2/Pad/LStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.lstick_left, "VirtualPad2/Pad/LStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.lstick_right, "VirtualPad2/Pad/LStick.Right");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.rstick_up, "VirtualPad2/Pad/RStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.rstick_down, "VirtualPad2/Pad/RStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.rstick_left, "VirtualPad2/Pad/RStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[1].pad.rstick_right, "VirtualPad2/Pad/RStick.Right");

    otherCursedAnalogMap.insert(virtualPorts[2].pad.l_trigger, "VirtualPad3/Pad/L.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.r_trigger, "VirtualPad3/Pad/R.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.lstick_up, "VirtualPad3/Pad/LStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.lstick_down, "VirtualPad3/Pad/LStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.lstick_left, "VirtualPad3/Pad/LStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.lstick_right, "VirtualPad3/Pad/LStick.Right");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.rstick_up, "VirtualPad3/Pad/RStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.rstick_down, "VirtualPad3/Pad/RStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.rstick_left, "VirtualPad3/Pad/RStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[2].pad.rstick_right, "VirtualPad3/Pad/RStick.Right");

    otherCursedAnalogMap.insert(virtualPorts[3].pad.l_trigger, "VirtualPad4/Pad/L.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.r_trigger, "VirtualPad4/Pad/R.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.lstick_up, "VirtualPad4/Pad/LStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.lstick_down, "VirtualPad4/Pad/LStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.lstick_left, "VirtualPad4/Pad/LStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.lstick_right, "VirtualPad4/Pad/LStick.Right");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.rstick_up, "VirtualPad4/Pad/RStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.rstick_down, "VirtualPad4/Pad/RStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.rstick_left, "VirtualPad4/Pad/RStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[3].pad.rstick_right, "VirtualPad4/Pad/RStick.Right");

    otherCursedAnalogMap.insert(virtualPorts[4].pad.l_trigger, "VirtualPad5/Pad/L.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.r_trigger, "VirtualPad5/Pad/R.Trigger");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.lstick_up, "VirtualPad5/Pad/LStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.lstick_down, "VirtualPad5/Pad/LStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.lstick_left, "VirtualPad5/Pad/LStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.lstick_right, "VirtualPad5/Pad/LStick.Right");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.rstick_up, "VirtualPad5/Pad/RStick.Up");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.rstick_down, "VirtualPad5/Pad/RStick.Down");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.rstick_left, "VirtualPad5/Pad/RStick.Left");
    otherCursedAnalogMap.insert(virtualPorts[4].pad.rstick_right, "VirtualPad5/Pad/RStick.Right");

    // MARK: digital

    otherCursedDigitalMap.insert(virtualPorts[0].mouse.left, "VirtualPad1/Mouse/Left");
    otherCursedDigitalMap.insert(virtualPorts[0].mouse.middle, "VirtualPad1/Mouse/Middle");
    otherCursedDigitalMap.insert(virtualPorts[0].mouse.right, "VirtualPad1/Mouse/Right");
    otherCursedDigitalMap.insert(virtualPorts[0].mouse.extra, "VirtualPad1/Mouse/Extra");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.one, "VirtualPad1/Pad/One");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.two, "VirtualPad1/Pad/Two");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.three, "VirtualPad1/Pad/Three");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.four, "VirtualPad1/Pad/Four");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.five, "VirtualPad1/Pad/Five");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.six, "VirtualPad1/Pad/Six");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.seven, "VirtualPad1/Pad/Seven");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.eight, "VirtualPad1/Pad/Eight");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.nine, "VirtualPad1/Pad/Nine");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.zero, "VirtualPad1/Pad/Zero");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.star, "VirtualPad1/Pad/Star");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.clear, "VirtualPad1/Pad/Clear");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.pound, "VirtualPad1/Pad/Pound");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.point, "VirtualPad1/Pad/Point");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.end, "VirtualPad1/Pad/End");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.lstick_click, "VirtualPad1/Pad/LStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.rstick_click, "VirtualPad1/Pad/RStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.up, "VirtualPad1/Pad/Up");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.down, "VirtualPad1/Pad/Down");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.left, "VirtualPad1/Pad/Left");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.right, "VirtualPad1/Pad/Right");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.select, "VirtualPad1/Pad/Select");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.start, "VirtualPad1/Pad/Start");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.south, "VirtualPad1/Pad/South");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.east, "VirtualPad1/Pad/East");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.west, "VirtualPad1/Pad/West");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.north, "VirtualPad1/Pad/North");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.l_bumper, "VirtualPad1/Pad/L.Bumper");
    otherCursedDigitalMap.insert(virtualPorts[0].pad.r_bumper, "VirtualPad1/Pad/R.Bumper");

    otherCursedDigitalMap.insert(virtualPorts[1].mouse.left, "VirtualPad2/Mouse/Left");
    otherCursedDigitalMap.insert(virtualPorts[1].mouse.middle, "VirtualPad2/Mouse/Middle");
    otherCursedDigitalMap.insert(virtualPorts[1].mouse.right, "VirtualPad2/Mouse/Right");
    otherCursedDigitalMap.insert(virtualPorts[1].mouse.extra, "VirtualPad2/Mouse/Extra");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.one, "VirtualPad2/Pad/One");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.two, "VirtualPad2/Pad/Two");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.three, "VirtualPad2/Pad/Three");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.four, "VirtualPad2/Pad/Four");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.five, "VirtualPad2/Pad/Five");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.six, "VirtualPad2/Pad/Six");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.seven, "VirtualPad2/Pad/Seven");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.eight, "VirtualPad2/Pad/Eight");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.nine, "VirtualPad2/Pad/Nine");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.zero, "VirtualPad2/Pad/Zero");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.star, "VirtualPad2/Pad/Star");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.clear, "VirtualPad2/Pad/Clear");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.pound, "VirtualPad2/Pad/Pound");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.point, "VirtualPad2/Pad/Point");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.end, "VirtualPad2/Pad/End");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.lstick_click, "VirtualPad2/Pad/LStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.rstick_click, "VirtualPad2/Pad/RStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.up, "VirtualPad2/Pad/Up");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.down, "VirtualPad2/Pad/Down");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.left, "VirtualPad2/Pad/Left");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.right, "VirtualPad2/Pad/Right");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.select, "VirtualPad2/Pad/Select");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.start, "VirtualPad2/Pad/Start");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.south, "VirtualPad2/Pad/South");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.east, "VirtualPad2/Pad/East");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.west, "VirtualPad2/Pad/West");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.north, "VirtualPad2/Pad/North");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.l_bumper, "VirtualPad2/Pad/L.Bumper");
    otherCursedDigitalMap.insert(virtualPorts[1].pad.r_bumper, "VirtualPad2/Pad/R.Bumper");

    otherCursedDigitalMap.insert(virtualPorts[2].mouse.left, "VirtualPad3/Mouse/Left");
    otherCursedDigitalMap.insert(virtualPorts[2].mouse.middle, "VirtualPad3/Mouse/Middle");
    otherCursedDigitalMap.insert(virtualPorts[2].mouse.right, "VirtualPad3/Mouse/Right");
    otherCursedDigitalMap.insert(virtualPorts[2].mouse.extra, "VirtualPad3/Mouse/Extra");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.one, "VirtualPad3/Pad/One");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.two, "VirtualPad3/Pad/Two");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.three, "VirtualPad3/Pad/Three");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.four, "VirtualPad3/Pad/Four");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.five, "VirtualPad3/Pad/Five");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.six, "VirtualPad3/Pad/Six");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.seven, "VirtualPad3/Pad/Seven");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.eight, "VirtualPad3/Pad/Eight");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.nine, "VirtualPad3/Pad/Nine");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.zero, "VirtualPad3/Pad/Zero");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.star, "VirtualPad3/Pad/Star");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.clear, "VirtualPad3/Pad/Clear");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.pound, "VirtualPad3/Pad/Pound");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.point, "VirtualPad3/Pad/Point");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.end, "VirtualPad3/Pad/End");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.lstick_click, "VirtualPad3/Pad/LStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.rstick_click, "VirtualPad3/Pad/RStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.up, "VirtualPad3/Pad/Up");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.down, "VirtualPad3/Pad/Down");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.left, "VirtualPad3/Pad/Left");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.right, "VirtualPad3/Pad/Right");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.select, "VirtualPad3/Pad/Select");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.start, "VirtualPad3/Pad/Start");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.south, "VirtualPad3/Pad/South");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.east, "VirtualPad3/Pad/East");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.west, "VirtualPad3/Pad/West");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.north, "VirtualPad3/Pad/North");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.l_bumper, "VirtualPad3/Pad/L.Bumper");
    otherCursedDigitalMap.insert(virtualPorts[2].pad.r_bumper, "VirtualPad3/Pad/R.Bumper");

    otherCursedDigitalMap.insert(virtualPorts[3].mouse.left, "VirtualPad4/Mouse/Left");
    otherCursedDigitalMap.insert(virtualPorts[3].mouse.middle, "VirtualPad4/Mouse/Middle");
    otherCursedDigitalMap.insert(virtualPorts[3].mouse.right, "VirtualPad4/Mouse/Right");
    otherCursedDigitalMap.insert(virtualPorts[3].mouse.extra, "VirtualPad4/Mouse/Extra");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.one, "VirtualPad4/Pad/One");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.two, "VirtualPad4/Pad/Two");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.three, "VirtualPad4/Pad/Three");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.four, "VirtualPad4/Pad/Four");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.five, "VirtualPad4/Pad/Five");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.six, "VirtualPad4/Pad/Six");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.seven, "VirtualPad4/Pad/Seven");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.eight, "VirtualPad4/Pad/Eight");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.nine, "VirtualPad4/Pad/Nine");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.zero, "VirtualPad4/Pad/Zero");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.star, "VirtualPad4/Pad/Star");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.clear, "VirtualPad4/Pad/Clear");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.pound, "VirtualPad4/Pad/Pound");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.point, "VirtualPad4/Pad/Point");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.end, "VirtualPad4/Pad/End");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.lstick_click, "VirtualPad4/Pad/LStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.rstick_click, "VirtualPad4/Pad/RStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.up, "VirtualPad4/Pad/Up");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.down, "VirtualPad4/Pad/Down");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.left, "VirtualPad4/Pad/Left");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.right, "VirtualPad4/Pad/Right");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.select, "VirtualPad4/Pad/Select");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.start, "VirtualPad4/Pad/Start");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.south, "VirtualPad4/Pad/South");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.east, "VirtualPad4/Pad/East");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.west, "VirtualPad4/Pad/West");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.north, "VirtualPad4/Pad/North");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.l_bumper, "VirtualPad4/Pad/L.Bumper");
    otherCursedDigitalMap.insert(virtualPorts[3].pad.r_bumper, "VirtualPad4/Pad/R.Bumper");

    otherCursedDigitalMap.insert(virtualPorts[4].mouse.left, "VirtualPad5/Mouse/Left");
    otherCursedDigitalMap.insert(virtualPorts[4].mouse.middle, "VirtualPad5/Mouse/Middle");
    otherCursedDigitalMap.insert(virtualPorts[4].mouse.right, "VirtualPad5/Mouse/Right");
    otherCursedDigitalMap.insert(virtualPorts[4].mouse.extra, "VirtualPad5/Mouse/Extra");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.one, "VirtualPad5/Pad/One");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.two, "VirtualPad5/Pad/Two");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.three, "VirtualPad5/Pad/Three");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.four, "VirtualPad5/Pad/Four");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.five, "VirtualPad5/Pad/Five");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.six, "VirtualPad5/Pad/Six");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.seven, "VirtualPad5/Pad/Seven");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.eight, "VirtualPad5/Pad/Eight");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.nine, "VirtualPad5/Pad/Nine");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.zero, "VirtualPad5/Pad/Zero");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.star, "VirtualPad5/Pad/Star");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.clear, "VirtualPad5/Pad/Clear");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.pound, "VirtualPad5/Pad/Pound");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.point, "VirtualPad5/Pad/Point");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.end, "VirtualPad5/Pad/End");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.lstick_click, "VirtualPad5/Pad/LStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.rstick_click, "VirtualPad5/Pad/RStick.Click");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.up, "VirtualPad5/Pad/Up");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.down, "VirtualPad5/Pad/Down");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.left, "VirtualPad5/Pad/Left");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.right, "VirtualPad5/Pad/Right");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.select, "VirtualPad5/Pad/Select");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.start, "VirtualPad5/Pad/Start");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.south, "VirtualPad5/Pad/South");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.east, "VirtualPad5/Pad/East");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.west, "VirtualPad5/Pad/West");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.north, "VirtualPad5/Pad/North");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.l_bumper, "VirtualPad5/Pad/L.Bumper");
    otherCursedDigitalMap.insert(virtualPorts[4].pad.r_bumper, "VirtualPad5/Pad/R.Bumper");

    // MARK: relative

    otherCursedRelativeMap.insert(virtualPorts[0].mouse.x, "VirtualPad1/Mouse/X");
    otherCursedRelativeMap.insert(virtualPorts[0].mouse.y, "VirtualPad1/Mouse/Y");

    otherCursedRelativeMap.insert(virtualPorts[1].mouse.x, "VirtualPad2/Mouse/X");
    otherCursedRelativeMap.insert(virtualPorts[1].mouse.y, "VirtualPad2/Mouse/Y");

    otherCursedRelativeMap.insert(virtualPorts[2].mouse.x, "VirtualPad3/Mouse/X");
    otherCursedRelativeMap.insert(virtualPorts[2].mouse.y, "VirtualPad3/Mouse/Y");

    otherCursedRelativeMap.insert(virtualPorts[3].mouse.x, "VirtualPad4/Mouse/X");
    otherCursedRelativeMap.insert(virtualPorts[3].mouse.y, "VirtualPad4/Mouse/Y");

    otherCursedRelativeMap.insert(virtualPorts[4].mouse.x, "VirtualPad5/Mouse/X");
    otherCursedRelativeMap.insert(virtualPorts[4].mouse.y, "VirtualPad5/Mouse/Y");
  }*/


};
