auto EmulatorSettings::construct() -> void {
  setCollapsible();
  setVisible(false);
  
  defaultSettings.construct();
  n64Settings.construct();
  mega32XMegaCD32XMegaCDMegaDriveSettings.construct();
  
  layout.setPadding(-20_sx, -20_sy);
  emulatorPanelContainer.setPadding(20_sx, 20_sy);
  
  emulatorPanelContainer.append(defaultSettings, Size{~0, ~0});
  emulatorPanelContainer.append(n64Settings, Size{~0, ~0});
  emulatorPanelContainer.append(mega32XMegaCD32XMegaCDMegaDriveSettings, Size{~0, ~0});

  //emulatorLabel.setText("Load Menu Emulators").setFont(Font().setBold());
  emulatorList.onToggle([&](auto cell) { eventToggle(cell); });
  emulatorList.onChange([&] { eventChange(); });
  emulatorList.append(TableViewColumn());
  emulatorList.append(TableViewColumn().setText("Name").setExpandable());
  emulatorList.append(TableViewColumn().setText("Manufacturer").setAlignment(1.0));
  emulatorList.setHeadered();
  TableViewItem item{&emulatorList};
  TableViewCell visible{&item};
  TableViewCell name{&item};
  name.setText("Defaults");
  //TableViewCell manufacturer{&item};
  for(auto& emulator : emulators) {
    TableViewItem item{&emulatorList};
    item.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    TableViewCell visible{&item};
    visible.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    visible.setCheckable();
    visible.setChecked(emulator->configuration.visible);
    TableViewCell name{&item};
    name.setText(emulator->name);
    TableViewCell manufacturer{&item};
    manufacturer.setText(emulator->manufacturer);
  }
  emulatorList.resizeColumns();
  emulatorList.column(0).setWidth(16);
}

auto EmulatorSettings::eventChange() -> void {
  defaultSettings.setVisible(false);
  arcadeSettings.setVisible(false);
  a2600Settings.setVisible(false);
  colecoVisionSettings.setVisible(false);
  famicomSettings.setVisible(false);
  gameBoyAdvanceSettings.setVisible(false);
  gameBoyGameBoyColorSettings.setVisible(false);
  gameGearSettings.setVisible(false);
  masterSystemSettings.setVisible(false);
  mega32XMegaCD32XMegaCDMegaDriveSettings.setVisible(false);
  msxSettings.setVisible(false);
  msx2Settings.setVisible(false);
  myVisionSettings.setVisible(false);
  neoGeoSettings.setVisible(false);
  n64Settings.setVisible(false);
  pcEngineSettings.setVisible(false);
  playstationSettings.setVisible(false);
  pocketChallengeV2Settings.setVisible(false);
  saturnSettings.setVisible(false);
  sg1000Settings.setVisible(false);
  superFamicomSettings.setVisible(false);
  superGrafxSettings.setVisible(false);
  wonderSwanSettings.setVisible(false);
  zxSpectrumSettings.setVisible(false);

  bool found = false;
  auto item = emulatorList.selected();
  if(auto emulator = item.attribute<shared_pointer<Emulator>>("emulator")) {
    auto name = emulator->name;
    if(name == "arcadeSettings" ) found = true, arcadeSettings.setVisible();
    if(name == "a2600Settings" ) found = true, a2600Settings.setVisible();
    if(name == "colecoVisionSettings" ) found = true, colecoVisionSettings.setVisible();
    if(name == "famicomSettings" ) found = true, famicomSettings.setVisible();
    if(name == "gameBoyAdvanceSettings" ) found = true, gameBoyAdvanceSettings.setVisible();
    if(name == "gameBoyGameBoyColorSettings" ) found = true, gameBoyGameBoyColorSettings.setVisible();
    if(name == "gameGearSettings" ) found = true, gameGearSettings.setVisible();
    if(name == "masterSystemSettings" ) found = true, masterSystemSettings.setVisible();
    if(name == "Mega CD" ) found = true, mega32XMegaCD32XMegaCDMegaDriveSettings.setVisible();
    if(name == "msxSettings" ) found = true, msxSettings.setVisible();
    if(name == "msx2Settings" ) found = true, msx2Settings.setVisible();
    if(name == "myVisionSettings" ) found = true, myVisionSettings.setVisible();
    if(name == "neoGeoSettings" ) found = true, neoGeoSettings.setVisible();
    if(name == "Nintendo 64" ) found = true, n64Settings.setVisible();
    if(name == "pcEngineSettings" ) found = true, pcEngineSettings.setVisible();
    if(name == "playstationSettings" ) found = true, playstationSettings.setVisible();
    if(name == "pocketChallengeV2Settings" ) found = true, pocketChallengeV2Settings.setVisible();
    if(name == "saturnSettings" ) found = true, saturnSettings.setVisible();
    if(name == "sg1000Settings" ) found = true, sg1000Settings.setVisible();
    if(name == "superFamicomSettings" ) found = true, superFamicomSettings.setVisible();
    if(name == "superGrafxSettings" ) found = true, superGrafxSettings.setVisible();
    if(name == "wonderSwanSettings" ) found = true, wonderSwanSettings.setVisible();
    if(name == "zxSpectrumSettings" ) found = true, zxSpectrumSettings.setVisible();
  } else {
    found = true, defaultSettings.setVisible();
  }
  emulatorPanelContainer.resize();
}

auto EmulatorSettings::eventToggle(TableViewCell cell) -> void {
  if(auto emulator = cell.attribute<shared_pointer<Emulator>>("emulator")) {
    emulator->configuration.visible = cell.checked();
    presentation.loadEmulators();
  }
}

/// MARK: Default settings

auto DefaultSettings::construct() -> void {
  commonSettingsLabel.setText("System Options").setFont(Font().setBold());

  rewind.setText("Rewind").setChecked(settings.general.rewind).onToggle([&] {
    settings.general.rewind = rewind.checked();
    program.rewindReset();
  }).doToggle();
  rewindLayout.setAlignment(1).setPadding(12_sx, 0);
      rewindHint.setText("Allows you to reverse time via the rewind hotkey").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  runAhead.setText("Run-Ahead").setEnabled(co_serializable()).setChecked(settings.general.runAhead && co_serializable()).onToggle([&] {
    settings.general.runAhead = runAhead.checked() && co_serializable();
    program.runAheadUpdate();
  });
  runAheadLayout.setAlignment(1).setPadding(12_sx, 0);
      runAheadHint.setText("Removes one frame of input lag, but doubles system requirements").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  autoSaveMemory.setText("Auto-Save Memory Periodically").setChecked(settings.general.autoSaveMemory).onToggle([&] {
    settings.general.autoSaveMemory = autoSaveMemory.checked();
  });
  autoSaveMemoryLayout.setAlignment(1).setPadding(12_sx, 0);
      autoSaveMemoryHint.setText("Helps safeguard game saves from being lost").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  homebrewMode.setText("Homebrew Development Mode").setChecked(settings.general.homebrewMode).onToggle([&] {
    settings.general.homebrewMode = homebrewMode.checked();
  });
  homebrewModeLayout.setAlignment(1).setPadding(12_sx, 0);
      homebrewModeHint.setText("Activate core-specific features to help homebrew developers").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  forceInterpreter.setText("Force Interpreter").setChecked(settings.general.forceInterpreter).onToggle([&] {
    settings.general.forceInterpreter = forceInterpreter.checked();
  });
  forceInterpreterLayout.setAlignment(1).setPadding(12_sx, 0);
      forceInterpreterHint.setText("(Slow) Enable interpreter for cores that default to a recompiler").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  
  emulatorSettingsLabel.setText("Rendering Options").setFont(Font().setBold());
  colorBleedOption.setText("Color Bleed").setChecked(settings.video.colorBleed).onToggle([&] {
    settings.video.colorBleed = colorBleedOption.checked();
    if(emulator) emulator->setColorBleed(settings.video.colorBleed);
  });
  colorBleedLayout.setAlignment(1).setPadding(12_sx, 0);
  colorBleedHint.setText("Blurs adjacent pixels for translucency effects").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  colorEmulationOption.setText("Color Emulation").setChecked(settings.video.colorEmulation).onToggle([&] {
    settings.video.colorEmulation = colorEmulationOption.checked();
    if(emulator) emulator->setBoolean("Color Emulation", settings.video.colorEmulation);
  });
  colorEmulationLayout.setAlignment(1).setPadding(12_sx, 0);
  colorEmulationHint.setText("Matches colors to how they look on real hardware").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  deepBlackBoostOption.setText("Deep Black Boost").setChecked(settings.video.deepBlackBoost).onToggle([&] {
    settings.video.deepBlackBoost = deepBlackBoostOption.checked();
    if(emulator) emulator->setBoolean("Deep Black Boost", settings.video.deepBlackBoost);
  });
  deepBlackBoostLayout.setAlignment(1).setPadding(12_sx, 0);
  deepBlackBoostHint.setText("Applies a gamma ramp to crush black levels (SNES/SFC)").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  interframeBlendingOption.setText("Interframe Blending").setChecked(settings.video.interframeBlending).onToggle([&] {
    settings.video.interframeBlending = interframeBlendingOption.checked();
    if(emulator) emulator->setBoolean("Interframe Blending", settings.video.interframeBlending);
  });
  interframeBlendingLayout.setAlignment(1).setPadding(12_sx, 0);
  interframeBlendingHint.setText("Emulates LCD translucency effects, but increases motion blur").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  overscanOption.setText("Overscan").setChecked(settings.video.overscan).onToggle([&] {
    settings.video.overscan = overscanOption.checked();
    if(emulator) emulator->setOverscan(settings.video.overscan);
  });
  overscanLayout.setAlignment(1).setPadding(12_sx, 0);
  overscanHint.setText("Displays the full frame without cropping 'undesirable' borders").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  pixelAccuracyOption.setText("Pixel Accuracy Mode").setChecked(settings.video.pixelAccuracy).onToggle([&] {
    settings.video.pixelAccuracy = pixelAccuracyOption.checked();
    if(emulator) emulator->setBoolean("Pixel Accuracy", settings.video.pixelAccuracy);
  });
  pixelAccuracyLayout.setAlignment(1).setPadding(12_sx, 0);
  pixelAccuracyHint.setText("Use pixel-accurate emulation where available").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

}

/// MARK: MD settings

auto Mega32XMegaCD32XMegaCDMegaDriveSettings::construct() -> void {
  setCollapsible();
  megaDriveSettingsLabel.setText("Mega Drive Settings").setFont(Font().setBold());

  megaDriveTmssOption.setText("TMSS Boot Rom").setChecked(settings.megadrive.tmss).onToggle([&] {
    settings.megadrive.tmss = megaDriveTmssOption.checked();
  });
  megaDriveTmssLayout.setAlignment(1).setPadding(12_sx, 0);
    megaDriveTmssHint.setText("Enable/Disable the TMSS Boot Rom at system initialization").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}

/// MARK: N64 settings

auto N64Settings::construct() -> void {
  setCollapsible();
  renderSettingsLabel.setText("N64 Render Settings").setFont(Font().setBold());

  renderQualityLayout.setPadding(12_sx, 0);

  disableVideoInterfaceProcessingOption.setText("Disable Video Interface Processing").setChecked(settings.video.disableVideoInterfaceProcessing).onToggle([&] {
    settings.video.disableVideoInterfaceProcessing = disableVideoInterfaceProcessingOption.checked();
    if(emulator) emulator->setBoolean("Disable Video Interface Processing", settings.video.disableVideoInterfaceProcessing);
  });
  disableVideoInterfaceProcessingLayout.setAlignment(1).setPadding(12_sx, 0);
  disableVideoInterfaceProcessingHint.setText("Disables Video Interface post processing to render image from VRAM directly").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  weaveDeinterlacingOption.setText("Weave Deinterlacing").setChecked(settings.video.weaveDeinterlacing).onToggle([&] {
    settings.video.weaveDeinterlacing = weaveDeinterlacingOption.checked();
    if(emulator) emulator->setBoolean("(Experimental) Double the perceived vertical resolution; disabled when supersampling is used", settings.video.weaveDeinterlacing);
    if(weaveDeinterlacingOption.checked() == true) {
      renderSupersamplingOption.setChecked(false).setEnabled(false);
      settings.video.supersampling = false;
    } else {
      if(settings.video.quality != "SD") renderSupersamplingOption.setEnabled(true);
    }
  });
  weaveDeinterlacingLayout.setAlignment(1).setPadding(12_sx, 0);
  weaveDeinterlacingHint.setText("Doubles the perceived vertical resolution; incompatible with supersampling").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  renderQualitySD.setText("SD Quality").onActivate([&] {
    settings.video.quality = "SD";
    renderSupersamplingOption.setChecked(false).setEnabled(false);
    settings.video.supersampling = false;
    weaveDeinterlacingOption.setEnabled(true);
  });
  renderQualityHD.setText("HD Quality").onActivate([&] {
    settings.video.quality = "HD";
    if(weaveDeinterlacingOption.checked() == false) renderSupersamplingOption.setChecked(settings.video.supersampling).setEnabled(true);
  });
  renderQualityUHD.setText("UHD Quality").onActivate([&] {
    settings.video.quality = "UHD";
    if(weaveDeinterlacingOption.checked() == false) renderSupersamplingOption.setChecked(settings.video.supersampling).setEnabled(true);
  });
  if(settings.video.quality == "SD") renderQualitySD.setChecked();
  if(settings.video.quality == "HD") renderQualityHD.setChecked();
  if(settings.video.quality == "UHD") renderQualityUHD.setChecked();
  renderSupersamplingOption.setText("Supersampling").setChecked(settings.video.supersampling && settings.video.quality != "SD").setEnabled(settings.video.quality != "SD").onToggle([&] {
    settings.video.supersampling = renderSupersamplingOption.checked();
    if(renderSupersamplingOption.checked() == true) {
      weaveDeinterlacingOption.setEnabled(false).setChecked(false);
      settings.video.weaveDeinterlacing = false;
    } else {
      weaveDeinterlacingOption.setEnabled(true);
    }
  });
  renderSupersamplingLayout.setAlignment(1).setPadding(12_sx, 0);
  renderSupersamplingHint.setText("Scales HD and UHD resolutions back down to SD").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  renderSettingsLayout.setPadding(12_sx, 0);
  renderSettingsHint.setText("Note: render settings changes require a game reload to take effect").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  #if !defined(VULKAN)
  //hide Vulkan-specific options if Vulkan is not available
  renderSettingsLabel.setCollapsible(true).setVisible(false);
  renderQualityLayout.setCollapsible(true).setVisible(false);
  renderSupersamplingLayout.setCollapsible(true).setVisible(false);
  renderSettingsHint.setCollapsible(true).setVisible(false);
  disableVideoInterfaceProcessingLayout.setCollapsible(true).setVisible(false);
  weaveDeinterlacingLayout.setCollapsible(true).setVisible(false);
  #endif
  
  nintendo64SettingsLabel.setText("Nintendo 64 Settings").setFont(Font().setBold());

  nintendo64ExpansionPakOption.setText("4MB Expansion Pak").setChecked(settings.nintendo64.expansionPak).onToggle([&] {
    settings.nintendo64.expansionPak = nintendo64ExpansionPakOption.checked();
  });
  nintendo64ExpansionPakLayout.setAlignment(1).setPadding(12_sx, 0);
      nintendo64ExpansionPakHint.setText("Enable/Disable the 4MB Expansion Pak").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  for (auto& opt : array<string[4]>{"32KiB (Default)", "128KiB (Datel 1Meg)", "512KiB (Datel 4Meg)", "1984KiB (Maximum)"}) {
    ComboButtonItem item{&nintendo64ControllerPakBankOption};
    item.setText(opt);
    if (opt == settings.nintendo64.controllerPakBankString) {
      item.setSelected();

      if (opt == "32KiB (Default)") {
        settings.nintendo64.controllerPakBankCount = 1;
      } else if (opt == "128KiB (Datel 1Meg)") {
        settings.nintendo64.controllerPakBankCount = 4;
      } else if (opt == "512KiB (Datel 4Meg)") {
        settings.nintendo64.controllerPakBankCount = 16;
      } else if (opt == "1984KiB (Maximum)") {
        settings.nintendo64.controllerPakBankCount = 62;
      }
    }
  }
  nintendo64ControllerPakBankOption.onChange([&] {
    auto idx = nintendo64ControllerPakBankOption.selected();
    auto value = idx.text();
    if (value != settings.nintendo64.controllerPakBankString) {
      settings.nintendo64.controllerPakBankString = value;
      
      if (value == "32KiB (Default)") {
        settings.nintendo64.controllerPakBankCount = 1;
      } else if (value == "128KiB (Datel 1Meg)") {
        settings.nintendo64.controllerPakBankCount = 4;
      } else if (value == "512KiB (Datel 4Meg)") {
        settings.nintendo64.controllerPakBankCount = 16;
      } else if (value == "1984KiB (Maximum)") {
        settings.nintendo64.controllerPakBankCount = 62;
      }
    }
  });
  nintendo64ControllerPakBankLayout.setAlignment(1).setPadding(12_sx, 0);
      nintendo64ControllerPakBankLabel.setText("Controller Pak Size:");
      nintendo64ControllerPakBankHint.setText("Sets the size of a newly created Controller Pak's available memory").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}
