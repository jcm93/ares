#include "../desktop-ui.hpp"
#include "general.cpp"
#include "video.cpp"
#include "audio.cpp"
#include "input.cpp"
#include "hotkeys.cpp"
#include "emulators.cpp"
#include "firmware.cpp"
#include "overrides.cpp"
#include "paths.cpp"
#include "drivers.cpp"
#include "debug.cpp"
#include "home.cpp"

Settings settings;
namespace Instances { Instance<SettingsWindow> settingsWindow; }
SettingsWindow& settingsWindow = Instances::settingsWindow();
GeneralSettings& generalSettings = settingsWindow.generalSettings;
VideoSettings& videoSettings = settingsWindow.videoSettings;
AudioSettings& audioSettings = settingsWindow.audioSettings;
InputSettings& inputSettings = settingsWindow.inputSettings;
HotkeySettings& hotkeySettings = settingsWindow.hotkeySettings;
EmulatorSettings& emulatorSettings = settingsWindow.emulatorSettings;
FirmwareSettings& firmwareSettings = settingsWindow.firmwareSettings;
PathSettings& pathSettings = settingsWindow.pathSettings;
DebugSettings& debugSettings = settingsWindow.debugSettings;

auto Settings::load() -> void {
  auto settingsPath = locate("settings.bml");
  Markup::Node::operator=(BML::unserialize(string::read(settingsPath), " "));
  process(true);
  save();
}

auto Settings::save() -> void {
  process(false);
  auto settingsPath = locate("settings.bml");
  file::write(settingsPath, BML::serialize(*this, " "));
}

auto Settings::processBasic(bool load, string prefix, nall::shared_pointer<Emulator> emulator) -> void {

  #define bind(type, path, name) \
    if(load) { \
      if(auto node = operator[]({prefix, path})) { \
        name = node.type(); \
        if(prefix) emulator->settingsOverridesList.append(path); \
      } \
    } else { \
      if(prefix) { \
        if(emulator->settingsOverridesList.contains(path)) { \
          operator()({prefix, path}).setValue(name); \
        } \
      } else { \
        operator()({prefix, path}).setValue(name); \
      } \
    } \

  bind(string,  "Video/Driver", video.driver);
  bind(string,  "Video/Monitor", video.monitor);
  bind(string,  "Video/Format", video.format);
  bind(boolean, "Video/Exclusive", video.exclusive);
  bind(boolean, "Video/Blocking", video.blocking);
  bind(boolean, "Video/PresentSRGB", video.forceSRGB);
  bind(boolean, "Video/ThreadedRenderer", video.threadedRenderer);
  bind(boolean, "Video/NativeFullScreen", video.nativeFullScreen);
  bind(boolean, "Video/Flush", video.flush);
  bind(string,  "Video/Shader", video.shader);
  bind(natural, "Video/Multiplier", video.multiplier);
  bind(string,  "Video/Output", video.output);
  bind(string,  "Video/AspectCorrectionMode", video.aspectCorrection);
  bind(boolean, "Video/AdaptiveSizing", video.adaptiveSizing);
  bind(boolean, "Video/AutoCentering", video.autoCentering);
  bind(real,    "Video/Luminance", video.luminance);
  bind(real,    "Video/Saturation", video.saturation);
  bind(real,    "Video/Gamma", video.gamma);
  bind(boolean, "Video/ColorBleed", video.colorBleed);
  bind(boolean, "Video/ColorEmulation", video.colorEmulation);
  bind(boolean, "Video/DeepBlackBoost", video.deepBlackBoost);
  bind(boolean, "Video/InterframeBlending", video.interframeBlending);
  bind(boolean, "Video/Overscan", video.overscan);
  bind(boolean, "Video/PixelAccuracy", video.pixelAccuracy);

  bind(string,  "Audio/Driver", audio.driver);
  bind(string,  "Audio/Device", audio.device);
  bind(natural, "Audio/Frequency", audio.frequency);
  bind(natural, "Audio/Latency", audio.latency);
  bind(boolean, "Audio/Exclusive", audio.exclusive);
  bind(boolean, "Audio/Blocking", audio.blocking);
  bind(boolean, "Audio/Dynamic", audio.dynamic);
  bind(boolean, "Audio/Mute", audio.mute);
  bind(real,    "Audio/Volume", audio.volume);
  bind(real,    "Audio/Balance", audio.balance);

  bind(string,  "Input/Driver", input.driver);
  bind(string,  "Input/Defocus", input.defocus);

  bind(boolean, "Boot/Fast", boot.fast);
  bind(boolean, "Boot/Debugger", boot.debugger);
  bind(string,  "Boot/Prefer", boot.prefer);

  bind(boolean, "General/ShowStatusBar", general.showStatusBar);
  bind(boolean, "General/Rewind", general.rewind);
  bind(boolean, "General/RunAhead", general.runAhead);
  bind(boolean, "General/AutoSaveMemory", general.autoSaveMemory);
  bind(boolean, "General/HomebrewMode", general.homebrewMode);
  bind(boolean, "General/ForceInterpreter", general.forceInterpreter);

  bind(natural, "Rewind/Length", rewind.length);
  bind(natural, "Rewind/Frequency", rewind.frequency);

  bind(string,  "Paths/Home", paths.home);
  bind(string,  "Paths/Firmware", paths.firmware);
  bind(string,  "Paths/Saves", paths.saves);
  bind(string,  "Paths/Screenshots", paths.screenshots);
  bind(string,  "Paths/Debugging", paths.debugging);

  bind(natural, "DebugServer/Port", debugServer.port);
  bind(boolean, "DebugServer/Enabled", debugServer.enabled);
  bind(boolean, "DebugServer/UseIPv4", debugServer.useIPv4);

  #undef bind
}

auto Settings::process(bool load) -> void {
  if(load) {
    //initialize non-static default settings
    video.driver = ruby::Video::optimalDriver();
    audio.driver = ruby::Audio::optimalDriver();
    input.driver = ruby::Input::optimalDriver();
  }

  #define bind(type, path, name) \
    if(load) { \
      if(auto node = operator[](path)) name = node.type(); \
    } else { \
      operator()(path).setValue(name); \
    } \

  processBasic(load, "", nullptr);

#ifdef CORE_N64
  if(!nintendo64) nintendo64 = new N64Settings;
  bind(string,  "Nintendo64/Video/Quality", nintendo64->video.quality);
  bind(boolean, "Nintendo64/Video/Supersampling", nintendo64->video.supersampling);
  bind(boolean, "Nintendo64/Video/DisableVideoInterfaceProcessing", nintendo64->video.disableVideoInterfaceProcessing);
  bind(boolean, "Nintendo64/Video/WeaveDeinterlacing", nintendo64->video.weaveDeinterlacing);
  bind(boolean, "Nintendo64/System/ExpansionPak", nintendo64->system.expansionPak);
  bind(string,  "Nintendo64/System/ControllerPakBankString", nintendo64->system.controllerPakBankString);
#endif

#ifdef CORE_GBA
  if(!gameBoyAdvance) gameBoyAdvance = new GBASettings;
  bind(boolean, "GameBoyAdvance/Player", gameBoyAdvance->system.player);
#endif

#ifdef CORE_MD
  if(!megaDrive) megaDrive = new MDSettings;
  bind(boolean, "MegaDrive/TMSS", megaDrive->system.tmss);
#endif

#ifdef CORE_SFC
  if(!superFamicom) superFamicom = new SFCSettings;
  bind(string,  "Paths/SuperFamicom/GameBoy", superFamicom->paths.gameBoy);
  bind(string,  "Paths/SuperFamicom/BSMemory", superFamicom->paths.bsMemory);
  bind(string,  "Paths/SuperFamicom/SufamiTurbo", superFamicom->paths.sufamiTurbo);
#endif

  bind(string,  "Paths/ArcadeRoms", paths.arcadeRoms);

  for(u32 index : range(9)) {
    string name = {"Recent/Game-", 1 + index};
    bind(string, name, recent.game[index]);
  }

  for(u32 index : range(5)) {
    auto& port = virtualPorts[index];
    for(auto& input : port.pad.inputs) {
      string name = {"VirtualPad", 1 + index, "/", string{input.name}.replace(" ", ".").replace("(", ".").replace(")", "")}, value;
      if(load == 0) for(auto& assignment : input.mapping->assignments) value.append(assignment, ";");
      if(load == 0) value.trimRight(";", 1L);
      bind(string, name, value);
      if(load == 1) for(u32 binding : range(BindingLimit)) input.mapping->assignments[binding] = value.split(";")(binding);
    }
    for(auto& input : port.mouse.inputs) {
      string name = {"VirtualMouse", 1 + index, "/", input.name}, value;
      if(load == 0) for(auto& assignment : input.mapping->assignments) value.append(assignment, ";");
      if(load == 0) value.trimRight(";", 1L);
      bind(string, name, value);
      if(load == 1) for(u32 binding : range(BindingLimit)) input.mapping->assignments[binding] = value.split(";")(binding);
    }
  }

  for(auto& mapping : inputManager.hotkeys) {
    string name = {"Hotkey/", string{mapping.name}.replace(" ", "")}, value;
    if(load == 0) for(auto& assignment : mapping.assignments) value.append(assignment, ";");
    if(load == 0) value.trimRight(";", 1L);
    bind(string, name, value);
    if(load == 1) for(u32 binding : range(BindingLimit)) mapping.assignments[binding] = value.split(";")(binding);
  }

  for(auto& emulator : emulators) {
    if(!emulator->settingsOverrides) {
      emulator->settingsOverrides = new Settings;
    }
    string base = string{emulator->name}.replace(" ", ""), name;
    string overrides;
    if(load == 0) for(auto& settingOverride : emulator->settingsOverridesList) overrides.append(settingOverride, ";");
    if(load == 0) overrides.trimRight(";", 1L);
    name = {base, "/Overrides"};
    bind(string, base, overrides);
    if(load) {
      auto overridesList = overrides.split(";");
      emulator->settingsOverridesList = overridesList;
    }
    name = {base, "/Visible"};
    bind(boolean, name, emulator->configuration.visible);
    name = {base, "/Path"};
    bind(string,  name, emulator->configuration.game);
    for(auto& firmware : emulator->firmware) {
      string name = {base, "/Firmware/", firmware.type, ".", firmware.region};
      name.replace(" ", "-");
      bind(string, name, firmware.location);
    }
    processBasic(load, {base, "/"}, emulator);
  }

  #undef bind
}

//

auto SettingsWindow::initialize() -> void {
  onClose([&] {
    settings.save();
    setVisible(false);
    //cancel any pending input assignment requests, if any
    inputSettings.setVisible(false);
    hotkeySettings.setVisible(false);
  });

  panelContainer.setPadding(20_sx, 20_sy);
  
#if defined(Hiro_Toolbar)
  panelList.append(ToolbarItem().setText("General").setIcon(Icon::Action::Settings));
  panelList.append(ToolbarItem().setText("Video").setIcon(Icon::Device::Display));
  panelList.append(ToolbarItem().setText("Audio").setIcon(Icon::Device::Speaker));
  panelList.append(ToolbarItem().setText("Input").setIcon(Icon::Device::Joypad));
  panelList.append(ToolbarItem().setText("Hotkeys").setIcon(Icon::Device::Keyboard));
  panelList.append(ToolbarItem().setText("Emulators").setIcon(Icon::Place::Server));
  panelList.append(ToolbarItem().setText("Firmware").setIcon(Icon::Emblem::Binary));
  panelList.append(ToolbarItem().setText("Paths").setIcon(Icon::Emblem::Folder));
  panelList.append(ToolbarItem().setText("Debug").setIcon(Icon::Device::Network));
  panelList.setWindow(*this);
#else
  panelList.append(TabFrameItem().setText("General").setIcon(Icon::Action::Settings));
  panelList.append(TabFrameItem().setText("Video").setIcon(Icon::Device::Display));
  panelList.append(TabFrameItem().setText("Audio").setIcon(Icon::Device::Speaker));
  panelList.append(TabFrameItem().setText("Input").setIcon(Icon::Device::Joypad));
  panelList.append(TabFrameItem().setText("Hotkeys").setIcon(Icon::Device::Keyboard));
  panelList.append(TabFrameItem().setText("Emulators").setIcon(Icon::Place::Server));
  panelList.append(TabFrameItem().setText("Firmware").setIcon(Icon::Emblem::Binary));
  panelList.append(TabFrameItem().setText("Paths").setIcon(Icon::Emblem::Folder));
  panelList.append(TabFrameItem().setText("Debug").setIcon(Icon::Device::Network));
#endif
  panelList.onChange([&] { eventChange(); });

  panelContainer.append(generalSettings, Size{~0, ~0});
  panelContainer.append(videoSettings, Size{~0, ~0});
  panelContainer.append(audioSettings, Size{~0, ~0});
  panelContainer.append(inputSettings, Size{~0, ~0});
  panelContainer.append(hotkeySettings, Size{~0, ~0});
  panelContainer.append(emulatorSettings, Size{~0, ~0});
  panelContainer.append(firmwareSettings, Size{~0, ~0});
  panelContainer.append(pathSettings, Size{~0, ~0});
  panelContainer.append(debugSettings, Size{~0, ~0});
  panelContainer.append(homePanel, Size{~0, ~0});

  generalSettings.construct();
  videoSettings.construct();
  audioSettings.construct();
  inputSettings.construct();
  hotkeySettings.construct();
  emulatorSettings.construct();
  firmwareSettings.construct();
  pathSettings.construct();
  debugSettings.construct();
  homePanel.construct();

  setDismissable();
  setTitle("Settings");
  setSize({875_sx, 465_sy});
  setAlignment({0.25, 0.25});
  videoSettings.videoRefresh();
  audioSettings.audioRefresh();
  generalSettings.refresh();
  inputSettings.inputRefresh();
  initialized = true;
  //setResizable(false);
}

auto SettingsWindow::show(const string& panel) -> void {
  if(!initialized) initialize();
  for(auto item : panelList.items()) {
    if(item.text() == panel) {
      item.setSelected();
      eventChange();
      break;
    }
  }
  setVisible();
  setFocused();
  panelList.setFocused();
}

auto SettingsWindow::eventChange() -> void {
  generalSettings.setVisible(false);
  videoSettings.setVisible(false);
  audioSettings.setVisible(false);
  inputSettings.setVisible(false);
  hotkeySettings.setVisible(false);
  emulatorSettings.setVisible(false);
  firmwareSettings.setVisible(false);
  pathSettings.setVisible(false);
  debugSettings.setVisible(false);
  homePanel.setVisible(false);

  bool found = false;
  if(auto item = panelList.selected()) {
    if(item.text() == "General"  ) found = true, generalSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 375_sy});
    if(item.text() == "Video"    ) found = true, videoSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 495_sy});
    if(item.text() == "Audio"    ) found = true, audioSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 290_sy});
    if(item.text() == "Input"    ) found = true, inputSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 475_sy});
    if(item.text() == "Hotkeys"  ) found = true, hotkeySettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 475_sy});
    if(item.text() == "Emulators") found = true, emulatorSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 475_sy});
    if(item.text() == "Firmware" ) found = true, firmwareSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 475_sy});
    if(item.text() == "Paths"    ) found = true, pathSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 350_sy});
    if(item.text() == "Debug"    ) found = true, debugSettings.setVisible(), *this->setSize(Size{sx(settingsWidth), 180_sy});
  }
  if(!found) homePanel.setVisible();

  panelContainer.resize();
}
