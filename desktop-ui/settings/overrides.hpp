
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

  std::vector<Override> overrides = {
    { .settingName = "Video Backend", .settingKey = "Video/Driver", .settingType = "string", },
    //{ .settingName = "Monitor", .settingKey = "Video/Monitor", .settingType = "string", },
    //{ .settingName = "Video Format", .settingKey = "Video/Format", .settingType = "string", },
    //{ .settingName = "Exclusive Video", .settingKey = "Video/Exclusive", .settingType = "boolean" },
    { .settingName = "Sync Mode", .settingKey = "Video/Blocking", .settingType = "boolean" },
    { .settingName = "Force sRGB", .settingKey = "Video/PresentSRGB", .settingType = "boolean" },
    //{ .settingName = "Threaded renderer", .settingKey = "Video/ThreadedRenderer", .settingType = "boolean" },
    //{ .settingName = "Use native fullscreen", .settingKey = "Video/NativeFullScreen", .settingType = "boolean" },
    //{ .settingName = "GPU Sync", .settingKey = "Video/Flush", .settingType = "boolean" },
    { .settingName = "Shader Preset", .settingKey = "Video/Shader", .settingType = "string", },
    //{ .settingName = "Video Scale", .settingKey = "Video/Multiplier", .settingType = "natural" },
    //{ .settingName = "Video Output Type", .settingKey = "Video/Output", .settingType = "string", },
    //{ .settingName = "Aspect Correction", .settingKey = "Video/AspectCorrectionMode", .settingType = "string", },
    //{ .settingName = "Adaptive Sizing", .settingKey = "Video/AdaptiveSizing", .settingType = "boolean" },
    //{ .settingName = "Auto Centering", .settingKey = "Video/AutoCentering", .settingType = "boolean" },
    { .settingName = "Luminance", .settingKey = "Video/Luminance", .settingType = "real", },
    { .settingName = "Saturation", .settingKey = "Video/Saturation", .settingType = "real", },
    { .settingName = "Gamma", .settingKey = "Video/Gamma", .settingType = "real", },
    { .settingName = "Color Bleed", .settingKey = "Video/ColorBleed", .settingType = "boolean" },
    { .settingName = "Color Emulation", .settingKey = "Video/ColorEmulation", .settingType = "boolean" },
    { .settingName = "Deep Black Boost", .settingKey = "Video/DeepBlackBoost", .settingType = "boolean" },
    { .settingName = "Interframe Blending", .settingKey = "Video/InterframeBlending", .settingType = "boolean" },
    { .settingName = "Overscan", .settingKey = "Video/Overscan", .settingType = "boolean" },
    { .settingName = "Pixel Accuracy", .settingKey = "Video/PixelAccuracy", .settingType = "boolean" },
    //{ .settingName = "Audio Backend", .settingKey = "Audio/Driver", .settingType = "string", },
    //{ .settingName = "Audio Device", .settingKey = "Audio/Device", .settingType = "string", },
    //{ .settingName = "Sample Rate", .settingKey = "Audio/Frequency", .settingType = "natural" },
    { .settingName = "Latency", .settingKey = "Audio/Latency", .settingType = "natural" },
    //{ .settingName = "Exclusive Audio", .settingKey = "Audio/Exclusive", .settingType = "boolean" },
    //{ .settingName = "Audio Blocking", .settingKey = "Audio/Blocking", .settingType = "boolean" },
    //{ .settingName = "Dynamic Rate Audio", .settingKey = "Audio/Dynamic", .settingType = "boolean" },
    //{ .settingName = "Mute", .settingKey = "Audio/Mute", .settingType = "boolean" },
    //{ .settingName = "Volume", .settingKey = "Audio/Volume", .settingType = "real", },
    //{ .settingName = "Balance", .settingKey = "Audio/Balance", .settingType = "real", },
    //{ .settingName = "Input Backend", .settingKey = "Input/Driver", .settingType = "string", },
    { .settingName = "Input Defocus Behavior", .settingKey = "Input/Defocus", .settingType = "string", },
    { .settingName = "Fast Boot", .settingKey = "Boot/Fast", .settingType = "boolean" },
    { .settingName = "Enable Tracer", .settingKey = "Boot/Debugger", .settingType = "boolean" },
    { .settingName = "Region Preference", .settingKey = "Boot/Prefer", .settingType = "string", },
    //{ .settingName = "Show Status Bar", .settingKey = "General/ShowStatusBar", .settingType = "boolean" },
    { .settingName = "Rewind", .settingKey = "General/Rewind", .settingType = "boolean" },
    { .settingName = "Run-ahead", .settingKey = "General/RunAhead", .settingType = "boolean" },
    { .settingName = "Auto Save Memory", .settingKey = "General/AutoSaveMemory", .settingType = "boolean" },
    { .settingName = "Rewind Length", .settingKey = "Rewind/Length", .settingType = "natural" },
    { .settingName = "Rewind Frequency", .settingKey = "Rewind/Frequency", .settingType = "natural" },
    //{ .settingName = "Home Path", .settingKey = "Paths/Home", .settingType = "string", },
    { .settingName = "Firmware Path", .settingKey = "Paths/Firmware", .settingType = "string", },
    { .settingName = "Saves Path", .settingKey = "Paths/Saves", .settingType = "string", },
    { .settingName = "Screenshots Path", .settingKey = "Paths/Screenshots", .settingType = "string", },
    { .settingName = "Debugging Path", .settingKey = "Paths/Debugging", .settingType = "string", },
    //{ .settingName = "Debug Server Port", .settingKey = "DebugServer/Port", .settingType = "natural" },
    { .settingName = "Debug Server", .settingKey = "DebugServer/Enabled", .settingType = "boolean" }
    //{ .settingName = "Debug Server IPv4", .settingKey = "DebugServer/UseIPv4", .settingType = "boolean" }
  };
};


struct OverrideSettings : VerticalLayout {
  auto construct() -> void;
  std::shared_ptr<Emulator> system;
  OverrideDialog overrideDialog;
  TableView overrideTable{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Button addButton{&controlLayout, Size{80, 0}};
    Button removeButton{&controlLayout, Size{80, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
};
