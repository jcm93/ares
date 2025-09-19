auto EmulatorSettings::construct() -> void {
  setCollapsible();
  setVisible(false);

  layout.setPadding(-20_sx, -20_sy);
  emulatorSettingsContainer.setPadding(20_sx, 20_sy);

  emulatorTabFrame.append(TabFrameItem().setText("System Settings"));
  emulatorTabFrame.append(TabFrameItem().setText("Overrides"));
  emulatorTabFrame.onChange([&] { eventChange(); });

  emulatorSettingsContainer.append(n64Settings, Size{~0, ~0});
  emulatorSettingsContainer.append(mega32XMegaCD32XMegaCDMegaDriveSettings, Size{~0, ~0});
  emulatorSettingsContainer.append(overrideSettings, Size{~0, ~0});
  overrideSettings.construct();

  //emulatorLabel.setText("Load Menu Emulators").setFont(Font().setBold());
  emulatorList.onToggle([&](auto cell) { eventToggle(cell); });
  emulatorList.onChange([&] { eventChange(); });
  emulatorList.append(TableViewColumn());
  emulatorList.append(TableViewColumn().setText("Name").setExpandable());
  emulatorList.append(TableViewColumn().setText("Manufacturer").setAlignment(1.0));
  emulatorList.setHeadered();
  for(auto& emulator : emulators) {
    auto name = emulator->name;
    if(name == "arcadeSettings" ) arcadeSettings.system = emulator;
    if(name == "a2600Settings" ) a2600Settings.system = emulator;
    if(name == "colecoVisionSettings" ) colecoVisionSettings.system = emulator;
    if(name == "famicomSettings" ) famicomSettings.system = emulator;
    if(name == "gameBoyAdvanceSettings" ) gameBoyAdvanceSettings.system = emulator;
    if(name == "gameBoyGameBoyColorSettings" ) gameBoyGameBoyColorSettings.system = emulator;
    if(name == "gameGearSettings" ) gameGearSettings.system = emulator;
    if(name == "masterSystemSettings" ) masterSystemSettings.system = emulator;
    if(name == "Mega CD" ) {
      mega32XMegaCD32XMegaCDMegaDriveSettings.system = emulator;
      mega32XMegaCD32XMegaCDMegaDriveSettings.construct();
    }
    if(name == "msxSettings" ) msxSettings.system = emulator;
    if(name == "msx2Settings" ) msx2Settings.system = emulator;
    if(name == "myVisionSettings" ) myVisionSettings.system = emulator;
    if(name == "neoGeoSettings" ) neoGeoSettings.system = emulator;
    if(name == "Nintendo 64" ) {
      n64Settings.system = emulator;
      n64Settings.construct();
    }
    if(name == "pcEngineSettings" ) pcEngineSettings.system = emulator;
    if(name == "playstationSettings" ) playstationSettings.system = emulator;
    if(name == "pocketChallengeV2Settings" ) pocketChallengeV2Settings.system = emulator;
    if(name == "saturnSettings" ) saturnSettings.system = emulator;
    if(name == "sg1000Settings" ) sg1000Settings.system = emulator;
    if(name == "superFamicomSettings" ) superFamicomSettings.system = emulator;
    if(name == "superGrafxSettings" ) superGrafxSettings.system = emulator;
    if(name == "wonderSwanSettings" ) wonderSwanSettings.system = emulator;
    if(name == "zxSpectrumSettings" ) zxSpectrumSettings.system = emulator;
    TableViewItem item{&emulatorList};
    item.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    TableViewCell visible{&item};
    visible.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    visible.setCheckable();
    visible.setChecked(emulator->configuration.visible);
    TableViewCell cellName{&item};
    cellName.setText(emulator->name);
    TableViewCell manufacturer{&item};
    manufacturer.setText(emulator->manufacturer);
  }
  emulatorList.resizeColumns();
  emulatorList.column(0).setWidth(16_sx);
  eventChange();
}

auto EmulatorSettings::eventChange() -> void {
  overrideSettings.setVisible(false);
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
    if(emulatorTabFrame.selected().text() == "System Settings") {
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
    } else if(emulatorTabFrame.selected().text() == "Overrides") {
      overrideSettings.setVisible();
    }
  } else if(emulatorTabFrame.selected().text() == "Overrides") {
    overrideSettings.setVisible();
  }
  emulatorSettingsContainer.resize();
}

auto EmulatorSettings::eventToggle(TableViewCell cell) -> void {
  if(auto emulator = cell.attribute<shared_pointer<Emulator>>("emulator")) {
    emulator->configuration.visible = cell.checked();
    presentation.loadEmulators();
  }
}

/// MARK: MD settings

auto Mega32XMegaCD32XMegaCDMegaDriveSettings::construct() -> void {
  setCollapsible();
  megaDriveSettingsLabel.setText("Mega Drive Settings").setFont(Font().setBold());

  homebrewLabel.setText("Homebrew Mode:");
  homebrewCheck.setText("Activate core-specific features to help homebrew developers")
    .setChecked(settings.general.homebrewMode).onToggle([&] {
      //todo
      settings.general.homebrewMode = homebrewCheck.checked();
  });

  forceInterpreterLabel.setText("Force Interpreter:");
  forceInterpreterCheck.setText("Use interpreters over recompilers by default (slow)")
    .setChecked(settings.general.forceInterpreter).onToggle([&] {
      //todo
      settings.general.forceInterpreter = forceInterpreterCheck.checked();
  });

  megaDriveTmssOption.setText("TMSS Boot Rom").setChecked(settings.megaDrive->system.tmss).onToggle([&] {
    settings.megaDrive->system.tmss = megaDriveTmssOption.checked();
  });
  megaDriveTmssLayout.setAlignment(1).setPadding(12_sx, 0);
  megaDriveTmssHint.setText("Enable/Disable the TMSS Boot Rom at system initialization").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}

/// MARK: N64 settings

auto N64SettingsLayout::construct() -> void {
  setCollapsible();
  
  renderSettingsLabel.setText("N64 Render Settings").setFont(Font().setBold());

  renderQualityLayout.setPadding(12_sx, 0);

  homebrewLabel.setText("Homebrew Mode:");
  homebrewCheck.setText("Activate core-specific features to help homebrew developers")
    .setChecked(settings.general.homebrewMode).onToggle([&] {
      //todo
      settings.general.homebrewMode = homebrewCheck.checked();
  });

  forceInterpreterLabel.setText("Force Interpreter:");
  forceInterpreterCheck.setText("Use interpreters over recompilers by default (slow)")
    .setChecked(settings.general.forceInterpreter).onToggle([&] {
      //todo
      settings.general.forceInterpreter = forceInterpreterCheck.checked();
  });

  disableVideoInterfaceProcessingOption.setText("Disable Video Interface Processing").setChecked(settings.nintendo64->video.disableVideoInterfaceProcessing).onToggle([&] {
    settings.nintendo64->video.disableVideoInterfaceProcessing = disableVideoInterfaceProcessingOption.checked();
    if(emulator) emulator->setBoolean("Disable Video Interface Processing", settings.nintendo64->video.disableVideoInterfaceProcessing);
  });
  disableVideoInterfaceProcessingLayout.setAlignment(1).setPadding(12_sx, 0);
  disableVideoInterfaceProcessingHint.setText("Disables Video Interface post processing to render image from VRAM directly").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  weaveDeinterlacingOption.setText("Weave Deinterlacing").setChecked(settings.nintendo64->video.weaveDeinterlacing).onToggle([&] {
    settings.nintendo64->video.weaveDeinterlacing = weaveDeinterlacingOption.checked();
    if(emulator) emulator->setBoolean("(Experimental) Double the perceived vertical resolution; disabled when supersampling is used", settings.nintendo64->video.weaveDeinterlacing);
    if(weaveDeinterlacingOption.checked() == true) {
      renderSupersamplingOption.setChecked(false).setEnabled(false);
      settings.nintendo64->video.supersampling = false;
    } else {
      if(settings.nintendo64->video.quality != "SD") renderSupersamplingOption.setEnabled(true);
    }
  });
  weaveDeinterlacingLayout.setAlignment(1).setPadding(12_sx, 0);
  weaveDeinterlacingHint.setText("Doubles the perceived vertical resolution; incompatible with supersampling").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  renderQualitySD.setText("SD Quality").onActivate([&] {
    settings.nintendo64->video.quality = "SD";
    renderSupersamplingOption.setChecked(false).setEnabled(false);
    settings.nintendo64->video.supersampling = false;
    weaveDeinterlacingOption.setEnabled(true);
  });
  renderQualityHD.setText("HD Quality").onActivate([&] {
    settings.nintendo64->video.quality = "HD";
    if(weaveDeinterlacingOption.checked() == false) renderSupersamplingOption.setChecked(settings.nintendo64->video.supersampling).setEnabled(true);
  });
  renderQualityUHD.setText("UHD Quality").onActivate([&] {
    settings.nintendo64->video.quality = "UHD";
    if(weaveDeinterlacingOption.checked() == false) renderSupersamplingOption.setChecked(settings.nintendo64->video.supersampling).setEnabled(true);
  });
  if(settings.nintendo64->video.quality == "SD") renderQualitySD.setChecked();
  if(settings.nintendo64->video.quality == "HD") renderQualityHD.setChecked();
  if(settings.nintendo64->video.quality == "UHD") renderQualityUHD.setChecked();
  renderSupersamplingOption.setText("Supersampling").setChecked(settings.nintendo64->video.supersampling && settings.nintendo64->video.quality != "SD").setEnabled(settings.nintendo64->video.quality != "SD").onToggle([&] {
    settings.nintendo64->video.supersampling = renderSupersamplingOption.checked();
    if(renderSupersamplingOption.checked() == true) {
      weaveDeinterlacingOption.setEnabled(false).setChecked(false);
      settings.nintendo64->video.weaveDeinterlacing = false;
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

  nintendo64ExpansionPakOption.setText("4MB Expansion Pak").setChecked(settings.nintendo64->system.expansionPak).onToggle([&] {
    settings.nintendo64->system.expansionPak = nintendo64ExpansionPakOption.checked();
  });
  nintendo64ExpansionPakLayout.setAlignment(1).setPadding(12_sx, 0);
      nintendo64ExpansionPakHint.setText("Enable/Disable the 4MB Expansion Pak").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  for (auto& opt : array<string[4]>{"32KiB (Default)", "128KiB (Datel 1Meg)", "512KiB (Datel 4Meg)", "1984KiB (Maximum)"}) {
    ComboButtonItem item{&nintendo64ControllerPakBankOption};
    item.setText(opt);
    if (opt == settings.nintendo64->system.controllerPakBankString) {
      item.setSelected();

      if (opt == "32KiB (Default)") {
        settings.nintendo64->system.controllerPakBankCount = 1;
      } else if (opt == "128KiB (Datel 1Meg)") {
        settings.nintendo64->system.controllerPakBankCount = 4;
      } else if (opt == "512KiB (Datel 4Meg)") {
        settings.nintendo64->system.controllerPakBankCount = 16;
      } else if (opt == "1984KiB (Maximum)") {
        settings.nintendo64->system.controllerPakBankCount = 62;
      }
    }
  }
  nintendo64ControllerPakBankOption.onChange([&] {
    auto idx = nintendo64ControllerPakBankOption.selected();
    auto value = idx.text();
    if (value != settings.nintendo64->system.controllerPakBankString) {
      settings.nintendo64->system.controllerPakBankString = value;

      if (value == "32KiB (Default)") {
        settings.nintendo64->system.controllerPakBankCount = 1;
      } else if (value == "128KiB (Datel 1Meg)") {
        settings.nintendo64->system.controllerPakBankCount = 4;
      } else if (value == "512KiB (Datel 4Meg)") {
        settings.nintendo64->system.controllerPakBankCount = 16;
      } else if (value == "1984KiB (Maximum)") {
        settings.nintendo64->system.controllerPakBankCount = 62;
      }
    }
  });
  nintendo64ControllerPakBankLayout.setAlignment(1).setPadding(12_sx, 0);
      nintendo64ControllerPakBankLabel.setText("Controller Pak Size:");
      nintendo64ControllerPakBankHint.setText("Sets the size of a newly created Controller Pak's available memory").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}
