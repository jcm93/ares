#include "../desktop-ui.hpp"
#include "video.cpp"
#include "audio.cpp"
#include "input.cpp"
#include "hotkeys.cpp"
#include "emulators.cpp"
#include "options.cpp"
#include "firmware.cpp"
#include "paths.cpp"
#include "drivers.cpp"
#include "debug.cpp"
#include "home.cpp"

GlobalSettings settings;
namespace Instances { Instance<SettingsWindow> settingsWindow; }
SettingsWindow& settingsWindow = Instances::settingsWindow();
VideoSettings& videoSettings = settingsWindow.videoSettings;
AudioSettings& audioSettings = settingsWindow.audioSettings;
InputSettings& inputSettings = settingsWindow.inputSettings;
HotkeySettings& hotkeySettings = settingsWindow.hotkeySettings;
EmulatorSettings& emulatorSettings = settingsWindow.emulatorSettings;
FirmwareSettings& firmwareSettings = settingsWindow.firmwareSettings;
PathSettings& pathSettings = settingsWindow.pathSettings;
DebugSettings& debugSettings = settingsWindow.debugSettings;

auto SettingsNode::load() -> void {
  Markup::Node::operator=(BML::unserialize(string::read(locate("settings.bml")), " "));
  process(true);
  save();
}

auto SettingsNode::save() -> void {
  process(false);
  file::write(locate("settings.bml"), BML::serialize(*this, " "));
}

auto GlobalSettings::tempBind(maybe<string> prefixArg, bool load, Markup::Node receiver) -> void {
  #define bind(type, path, name) \
    if(load) { \
      if(auto node = receiver[path]) name = node.type(); \
    } else { \
      receiver(path).setValue(name); \
    } \

  string prefix;
  if(prefixArg) {
    prefix = {prefixArg.get(), "/"};
  } else {
    prefix = (string)"";
  }

  string prefixedName = {prefix, "Video/Driver"};
  bind(string,  prefixedName, video.driver);
  prefixedName = {prefix, "Video/Monitor"};
  bind(string,  prefixedName, video.monitor);
  prefixedName = {prefix, "Video/Format"};
  bind(string,  prefixedName, video.format);
  prefixedName = {prefix, "Video/Exclusive"};
  bind(boolean, prefixedName, video.exclusive);
  prefixedName = {prefix, "Video/Blocking"};
  bind(boolean, prefixedName, video.blocking);
  prefixedName = {prefix, "Video/PresentSRGB"};
  bind(boolean, prefixedName, video.forceSRGB);
  prefixedName = {prefix, "Video/ThreadedRenderer"};
  bind(boolean, prefixedName, video.threadedRenderer);
  prefixedName = {prefix, "Video/NativeFullScreen"};
  bind(boolean, prefixedName, video.nativeFullScreen);
  prefixedName = {prefix, "Video/Flush"};
  bind(boolean, prefixedName, video.flush);
  prefixedName = {prefix, "Video/Shader"};
  bind(string,  prefixedName, video.shader);
  prefixedName = {prefix, "Video/Multiplier"};
  bind(natural, prefixedName, video.multiplier);
  prefixedName = {prefix, "Video/Output"};
  bind(string,  prefixedName, video.output);
  prefixedName = {prefix, "Video/AspectCorrection"};
  bind(boolean, prefixedName, video.aspectCorrection);
  prefixedName = {prefix, "Video/AdaptiveSizing"};
  bind(boolean, prefixedName, video.adaptiveSizing);
  prefixedName = {prefix, "Video/AutoCentering"};
  bind(boolean, prefixedName, video.autoCentering);
  prefixedName = {prefix, "Video/Luminance"};
  bind(real,    prefixedName, video.luminance);
  prefixedName = {prefix, "Video/Saturation"};
  bind(real,    prefixedName, video.saturation);
  prefixedName = {prefix, "Video/Gamma"};
  bind(real,    prefixedName, video.gamma);
  prefixedName = {prefix, "Video/ColorBleed"};
  bind(boolean, prefixedName, video.colorBleed);
  prefixedName = {prefix, "Video/ColorEmulation"};
  bind(boolean, prefixedName, video.colorEmulation);
  prefixedName = {prefix, "Video/DeepBlackBoost"};
  bind(boolean, prefixedName, video.deepBlackBoost);
  prefixedName = {prefix, "Video/InterframeBlending"};
  bind(boolean, prefixedName, video.interframeBlending);
  prefixedName = {prefix, "Video/Overscan"};
  bind(boolean, prefixedName, video.overscan);
  prefixedName = {prefix, "Video/PixelAccuracy"};
  bind(boolean, prefixedName, video.pixelAccuracy);

  prefixedName = {prefix, "Audio/Driver"};
  bind(string,  prefixedName, audio.driver);
  prefixedName = {prefix, "Audio/Device"};
  bind(string,  prefixedName, audio.device);
  prefixedName = {prefix, "Audio/Frequency"};
  bind(natural, prefixedName, audio.frequency);
  prefixedName = {prefix, "Audio/Latency"};
  bind(natural, prefixedName, audio.latency);
  prefixedName = {prefix, "Audio/Exclusive"};
  bind(boolean, prefixedName, audio.exclusive);
  prefixedName = {prefix, "Audio/Blocking"};
  bind(boolean, prefixedName, audio.blocking);
  prefixedName = {prefix, "Audio/Dynamic"};
  bind(boolean, prefixedName, audio.dynamic);
  prefixedName = {prefix, "Audio/Mute"};
  bind(boolean, prefixedName, audio.mute);
  prefixedName = {prefix, "Audio/Volume"};
  bind(real,    prefixedName, audio.volume);
  prefixedName = {prefix, "Audio/Balance"};
  bind(real,    prefixedName, audio.balance);

  prefixedName = {prefix, "Input/Driver"};
  bind(string,  prefixedName, input.driver);
  prefixedName = {prefix, "Input/Defocus"};
  bind(string,  prefixedName, input.defocus);

  prefixedName = {prefix, "Boot/Fast"};
  bind(boolean, prefixedName, boot.fast);
  prefixedName = {prefix, "Boot/Debugger"};
  bind(boolean, prefixedName, boot.debugger);
  prefixedName = {prefix, "Boot/Prefer"};
  bind(string,  prefixedName, boot.prefer);

  prefixedName = {prefix, "General/ShowStatusBar"};
  bind(boolean, prefixedName, general.showStatusBar);
  prefixedName = {prefix, "General/Rewind"};
  bind(boolean, prefixedName, general.rewind);
  prefixedName = {prefix, "General/RunAhead"};
  bind(boolean, prefixedName, general.runAhead);
  prefixedName = {prefix, "General/AutoSaveMemory"};
  bind(boolean, prefixedName, general.autoSaveMemory);
  prefixedName = {prefix, "General/HomebrewMode"};
  bind(boolean, prefixedName, general.homebrewMode);
  prefixedName = {prefix, "General/ForceInterpreter"};
  bind(boolean, prefixedName, general.forceInterpreter);

  prefixedName = {prefix, "Rewind/Length"};
  bind(natural, prefixedName, rewind.length);
  prefixedName = {prefix, "Rewind/Frequency"};
  bind(natural, prefixedName, rewind.frequency);

  prefixedName = {prefix, "Paths/Home"};
  bind(string,  prefixedName, paths.home);
  prefixedName = {prefix, "Paths/Firmware"};
  bind(string,  prefixedName, paths.firmware);
  prefixedName = {prefix, "Paths/Saves"};
  bind(string,  prefixedName, paths.saves);
  prefixedName = {prefix, "Paths/Screenshots"};
  bind(string,  prefixedName, paths.screenshots);
  prefixedName = {prefix, "Paths/Debugging"};
  bind(string,  prefixedName, paths.debugging);
  prefixedName = {prefix, "Paths/ArcadeRoms"};
  bind(string,  prefixedName, paths.arcadeRoms);
  prefixedName = {prefix, "Paths/SuperFamicom/GameBoy"};
  bind(string,  prefixedName, paths.superFamicom.gameBoy);
  prefixedName = {prefix, "Paths/SuperFamicom/BSMemory"};
  bind(string,  prefixedName, paths.superFamicom.bsMemory);
  prefixedName = {prefix, "Paths/SuperFamicom/SufamiTurbo"};
  bind(string,  prefixedName, paths.superFamicom.sufamiTurbo);

  prefixedName = {prefix, "DebugServer/Port"};
  bind(natural, prefixedName, debugServer.port);
  prefixedName = {prefix, "DebugServer/Enabled"};
  bind(boolean, prefixedName, debugServer.enabled);
  prefixedName = {prefix, "DebugServer/UseIPv4"};
  bind(boolean, prefixedName, debugServer.useIPv4);

  prefixedName = {prefix, "GameBoyAdvance/Player"};
  bind(boolean, prefixedName, gameBoyAdvance.player);

  prefixedName = {prefix, "MegaDrive/TMSS"};
  bind(boolean, prefixedName, megadrive.tmss);
  #undef bind
}

auto GlobalSettings::process(bool load) -> void {
  if(load) {
    //initialize non-static default settings
    video.driver = ruby::Video::optimalDriver();
    audio.driver = ruby::Audio::optimalDriver();
    input.driver = ruby::Input::optimalDriver();
  }
  
  tempBind(nothing, load, *this);
  
  /*auto bind = [this, load](auto type, auto path, auto name) {
    if(load) {
      if(auto node = operator[](path)) name = node.type();
    } else {
      operator()(path).setValue(name);
    }
  };*/
  
#define bind(type, path, name) \
  if(load) { \
    if(auto node = operator[](path)) name = node.type(); \
  } else { \
    operator()(path).setValue(name); \
  } \

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
    string base = string{emulator->name}.replace(" ", ""), name;
    name = {base, "/Visible"};
    bind(boolean, name, emulator->configuration.visible);
    name = {base, "/Path"};
    bind(string,  name, emulator->configuration.game);
    for(auto& firmware : emulator->firmware) {
      string name = {base, "/Firmware/", firmware.type, ".", firmware.region};
      name.replace(" ", "-");
      bind(string, name, firmware.location);
    }
    emulator->systemSettingsObject.tempBind(base, load, emulator->systemSettingsObject);
    emulator->coreSettings->process(load);
    append(emulator->systemSettingsObject);
    append(*(emulator->coreSettings));
  }

  #undef bind
}

//

SettingsWindow::SettingsWindow() {
  onClose([&] {
    settings.save();
    setVisible(false);
    //cancel any pending input assignment requests, if any
    inputSettings.setVisible(false);
    hotkeySettings.setVisible(false);
  });

  panelContainer.setPadding(20_sx, 20_sy);
  
#if defined(PLATFORM_MACOS)
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

  panelContainer.append(videoSettings, Size{~0, ~0});
  panelContainer.append(audioSettings, Size{~0, ~0});
  panelContainer.append(inputSettings, Size{~0, ~0});
  panelContainer.append(hotkeySettings, Size{~0, ~0});
  panelContainer.append(emulatorSettings, Size{~0, ~0});
  panelContainer.append(firmwareSettings, Size{~0, ~0});
  panelContainer.append(pathSettings, Size{~0, ~0});
  panelContainer.append(debugSettings, Size{~0, ~0});
  panelContainer.append(homePanel, Size{~0, ~0});

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
  setTitle("Configuration");
  setSize({875_sx, 465_sy});
  setAlignment({0.25, 0.25});
  //setResizable(false);
}

auto SettingsWindow::show(const string& panel) -> void {
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
    if(item.text() == "Video"    ) found = true, videoSettings.setVisible();
    if(item.text() == "Audio"    ) found = true, audioSettings.setVisible();
    if(item.text() == "Input"    ) found = true, inputSettings.setVisible();
    if(item.text() == "Hotkeys"  ) found = true, hotkeySettings.setVisible();
    if(item.text() == "Emulators") found = true, emulatorSettings.setVisible();
    if(item.text() == "Firmware" ) found = true, firmwareSettings.setVisible();
    if(item.text() == "Paths"    ) found = true, pathSettings.setVisible();
    if(item.text() == "Debug"    ) found = true, debugSettings.setVisible();
  }
  if(!found) homePanel.setVisible();

  panelContainer.resize();
}
