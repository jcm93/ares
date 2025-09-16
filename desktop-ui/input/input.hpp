enum : u32 { BindingLimit = 3 };

struct InputMapping {
  enum class Qualifier : u32 { None, Lo, Hi, Rumble };

  auto bind() -> void;
  auto bind(u32 binding, string assignment) -> void;
  auto unbind() -> void;
  auto unbind(u32 binding) -> void;

  virtual auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool = 0;
  virtual auto value() -> s16 = 0;
  virtual auto pressed() -> bool { return false; }

  string assignments[BindingLimit];

  struct Binding {
    auto icon() -> multiFactorImage;
    auto text() -> string;

    std::shared_ptr<HID::Device> device;
    u64 deviceID;
    u32 groupID;
    u32 inputID;
    Qualifier qualifier = Qualifier::None;
  };
  Binding bindings[BindingLimit];
};

//0 or 1
struct InputDigital : InputMapping {
  using InputMapping::bind;
  auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool override;
  auto value() -> s16 override;
  auto pressed() -> bool override;
};

//0 ... +32767
struct InputAnalog : InputMapping {
  using InputMapping::bind;
  auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool override;
  auto value() -> s16 override;
  auto pressed() -> bool override;
};

//-32768 ... +32767
struct InputAbsolute : InputMapping {
  using InputMapping::bind;
  auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool override;
  auto value() -> s16 override;
};

//-32768 ... +32767
struct InputRelative : InputMapping {
  using InputMapping::bind;
  auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool override;
  auto value() -> s16 override;
};

//specifies a target joypad for force feedback
struct InputRumble : InputMapping {
  using InputMapping::bind;
  auto bind(u32 binding, std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> bool override;
  auto value() -> s16 override;
  auto rumble(u16 strong, u16 weak) -> void;
};

struct InputHotkey : InputDigital {
  InputHotkey(string name) : name(name) {}
  auto& onPress(std::function<void ()> press) { return this->press = press, *this; }
  auto& onRelease(std::function<void ()> release) { return this->release = release, *this; }
  auto value() -> s16 override;

  const string name;

private:
  std::function<void ()> press;
  std::function<void ()> release;
  s16 state = 0;
  friend struct InputManager;
};

struct InputNode {
  bool operator==(const InputNode& other) const {
    return type == other.type && name == other.name && mapping == other.mapping;
  }
  enum class Type : u32 { Digital, Analog, Absolute, Relative, Rumble };
  Type type;
  string name;
  InputMapping* mapping;
};

struct InputPair {
  enum class Type : u32 { Analog };
  Type type;
  string name;
  InputMapping* mappingLo;
  InputMapping* mappingHi;
};

struct InputDevice {
  auto digital(string name, InputMapping& mapping) -> void {
    inputs.push_back({InputNode::Type::Digital, name, &mapping});
  }

  auto analog(string name, InputMapping& mapping) -> void {
    inputs.push_back({InputNode::Type::Analog, name, &mapping});
  }

  auto absolute(string name, InputMapping& mapping) -> void {
    inputs.push_back({InputNode::Type::Absolute, name, &mapping});
  }

  auto relative(string name, InputMapping& mapping) -> void {
    inputs.push_back({InputNode::Type::Relative, name, &mapping});
  }

  auto rumble(string name, InputMapping& mapping) -> void {
    inputs.push_back({InputNode::Type::Rumble, name, &mapping});
  }

  auto analog(string name, InputMapping& mappingLo, InputMapping& mappingHi) -> void {
    pairs.push_back({InputPair::Type::Analog, name, &mappingLo, &mappingHi});
  }

  string name;
  std::vector<InputNode> inputs;
  std::vector<InputPair> pairs;
};

struct InputPort {
  auto append(InputDevice& device) -> void {
    devices.push_back(device);
  }

  string name;
  std::vector<InputDevice> devices;
};

struct VirtualPad : InputDevice {
  VirtualPad();

  InputDigital up;
  InputDigital down;
  InputDigital left;
  InputDigital right;
  InputDigital select;
  InputDigital start;
  InputDigital south;
  InputDigital east;
  InputDigital west;
  InputDigital north;
  InputDigital l_bumper;
  InputDigital r_bumper;
  InputAnalog  l_trigger;
  InputAnalog  r_trigger;
  InputDigital lstick_click;
  InputDigital rstick_click;
  InputAnalog  lstick_up;
  InputAnalog  lstick_down;
  InputAnalog  lstick_left;
  InputAnalog  lstick_right;
  InputAnalog  rstick_up;
  InputAnalog  rstick_down;
  InputAnalog  rstick_left;
  InputAnalog  rstick_right;
  InputRumble  rumble;
  InputDigital one;
  InputDigital two;
  InputDigital three;
  InputDigital four;
  InputDigital five;
  InputDigital six;
  InputDigital seven;
  InputDigital eight;
  InputDigital nine;
  InputDigital zero;
  InputDigital star;
  InputDigital clear;
  InputDigital pound;
  InputDigital point;
  InputDigital end;
};

struct VirtualMouse : InputDevice {
  VirtualMouse();

  InputRelative x;
  InputRelative y;
  InputDigital  left;
  InputDigital  middle;
  InputDigital  right;
  InputDigital  extra;
};

struct VirtualPort {
  VirtualPad   pad;
  VirtualMouse mouse;
};

struct SystemVirtualPadMapping : InputDevice {

  InputNode up {InputNode::Type::Digital,  "up"};
  InputNode down = {InputNode::Type::Digital,  "down"};
  InputNode left = {InputNode::Type::Digital,  "left"};
  InputNode right = {InputNode::Type::Digital,  "right"};
  InputNode select = {InputNode::Type::Digital,  "select"};
  InputNode start = {InputNode::Type::Digital,  "start"};
  InputNode south = {InputNode::Type::Digital,  "south"};
  InputNode east = {InputNode::Type::Digital,  "east"};
  InputNode west = {InputNode::Type::Digital,  "west"};
  InputNode north = {InputNode::Type::Digital,  "north"};
  InputNode l_bumper = {InputNode::Type::Digital,  "l_bumper"};
  InputNode r_bumper = {InputNode::Type::Digital,  "r_bumper"};
  InputNode l_trigger = {InputNode::Type::Analog,  "l_trigger"};
  InputNode r_trigger = {InputNode::Type::Analog,  "r_trigger"};
  InputNode lstick_click = {InputNode::Type::Digital,  "lstick_click"};
  InputNode rstick_click = {InputNode::Type::Digital,  "rstick_click"};
  InputNode lstick_up = {InputNode::Type::Analog,  "lstick_up"};
  InputNode lstick_down = {InputNode::Type::Analog,  "lstick_down"};
  InputNode lstick_left = {InputNode::Type::Analog,  "lstick_left"};
  InputNode lstick_right = {InputNode::Type::Analog,  "lstick_right"};
  InputNode rstick_up = {InputNode::Type::Analog,  "rstick_up"};
  InputNode rstick_down = {InputNode::Type::Analog,  "rstick_down"};
  InputNode rstick_left = {InputNode::Type::Analog,  "rstick_left"};
  InputNode rstick_right = {InputNode::Type::Analog,  "rstick_right"};
  InputNode rumble = {InputNode::Type::Rumble,  "rumble"};
  InputNode one = {InputNode::Type::Digital,  "one"};
  InputNode two = {InputNode::Type::Digital,  "two"};
  InputNode three = {InputNode::Type::Digital,  "three"};
  InputNode four = {InputNode::Type::Digital,  "four"};
  InputNode five = {InputNode::Type::Digital,  "five"};
  InputNode six = {InputNode::Type::Digital,  "six"};
  InputNode seven = {InputNode::Type::Digital,  "seven"};
  InputNode eight = {InputNode::Type::Digital,  "eight"};
  InputNode nine = {InputNode::Type::Digital,  "nine"};
  InputNode zero = {InputNode::Type::Digital,  "zero"};
  InputNode star = {InputNode::Type::Digital,  "star"};
  InputNode clear = {InputNode::Type::Digital,  "clear"};
  InputNode pound = {InputNode::Type::Digital,  "pound"};
  InputNode point = {InputNode::Type::Digital,  "point"};
  InputNode end = {InputNode::Type::Digital,  "end"};
};

struct SystemVirtualMouseMapping : InputDevice {

  InputNode x;
  InputNode y;
  InputNode left;
  InputNode middle;
  InputNode right;
  InputNode extra;
};

struct SystemVirtualPadMappingPort {
  SystemVirtualPadMapping pad;
  SystemVirtualMouseMapping mouse;
};

struct InputManager {
  auto create() -> void;
  auto bind() -> void;
  auto poll(bool force = false) -> void;
  auto eventInput(std::shared_ptr<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void;

  //hotkeys.cpp
  auto createHotkeys() -> void;
  auto pollHotkeys() -> void;

  std::vector<std::shared_ptr<HID::Device>> devices;
  std::vector<InputHotkey> hotkeys;

  u64 pollFrequency = 5;
  u64 lastPoll = 0;
};

extern VirtualPort virtualPorts[5];
extern InputManager inputManager;
