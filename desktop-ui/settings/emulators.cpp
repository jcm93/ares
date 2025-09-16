auto EmulatorSettings::construct() -> void {
  setCollapsible();
  setVisible(false);

  layout.setPadding(-20_sx, -20_sy);
  emulatorSettingsContainer.setPadding(20_sx, 20_sy);

  emulatorTabFrame.append(TabFrameItem().setText("System Settings"));
  emulatorTabFrame.append(TabFrameItem().setText("Input"));
  emulatorTabFrame.onChange([&] { eventChange(); });

  emulatorList.onToggle([&](auto cell) { eventToggle(cell); });
  emulatorList.onChange([&] { eventChange(); });
  emulatorList.append(TableViewColumn().setText("Name").setExpandable());
  emulatorList.append(TableViewColumn().setText("Manufacturer").setAlignment(1.0));
  emulatorList.setHeadered();

  homePanel.construct();
  emulatorSettingsContainer.append(homePanel, Size{~0, ~0});
  emulatorSettingsContainer.append(systemInputSettings, Size{~0, ~0});
  systemInputSettings.setCollapsible();
  systemInputSettings.construct();

  for(auto& emulator : emulators) {
    auto name = emulator->name;
    if(name == "Arcade" ) {
      arcadeSettings.construct(emulator);
      emulatorSettingsContainer.append(arcadeSettings, Size{~0, ~0});
    } else if(name == "Atari 2600") {
      a2600Settings.construct(emulator);
      emulatorSettingsContainer.append(a2600Settings, Size{~0, ~0});
    } else if(name == "WonderSwan") {
      wonderSwanSettings.construct(emulator);
      emulatorSettingsContainer.append(wonderSwanSettings, Size{~0, ~0});
    } else if(name == "WonderSwan Color") {
      wonderSwanColorSettings.construct(emulator);
      emulatorSettingsContainer.append(wonderSwanColorSettings, Size{~0, ~0});
    } else if(name == "Pocket Challenge V2") {
      pocketChallengeV2Settings.construct(emulator);
      emulatorSettingsContainer.append(pocketChallengeV2Settings, Size{~0, ~0});
    } else if(name == "ColecoVision") {
      colecoVisionSettings.construct(emulator);
      emulatorSettingsContainer.append(colecoVisionSettings, Size{~0, ~0});
    } else if(name == "MyVision") {
      myVisionSettings.construct(emulator);
      emulatorSettingsContainer.append(myVisionSettings, Size{~0, ~0});
    } else if(name == "MSX") {
      msxSettings.construct(emulator);
      emulatorSettingsContainer.append(msxSettings, Size{~0, ~0});
    } else if(name == "MSX2") {
      msx2Settings.construct(emulator);
      emulatorSettingsContainer.append(msx2Settings, Size{~0, ~0});
    } else if(name == "PC Engine") {
      pcEngineSettings.construct(emulator);
      emulatorSettingsContainer.append(pcEngineSettings, Size{~0, ~0});
    } else if(name == "PC Engine CD") {
      pcEngineCDSettings.construct(emulator);
      emulatorSettingsContainer.append(pcEngineCDSettings, Size{~0, ~0});
    } else if(name == "LaserActive (NEC PAC)") {
      necPACSettings.construct(emulator);
      emulatorSettingsContainer.append(necPACSettings, Size{~0, ~0});
    } else if(name == "SuperGrafx") {
      superGrafxSettings.construct(emulator);
      emulatorSettingsContainer.append(superGrafxSettings, Size{~0, ~0});
    } else if(name == "SuperGrafx CD") {
      superGrafxCDSettings.construct(emulator);
      emulatorSettingsContainer.append(superGrafxCDSettings, Size{~0, ~0});
    } else if(name == "Famicom") {
      famicomSettings.construct(emulator);
      emulatorSettingsContainer.append(famicomSettings, Size{~0, ~0});
    } else if(name == "Famicom Disk System") {
      famicomDiskSystemSettings.construct(emulator);
      emulatorSettingsContainer.append(famicomDiskSystemSettings, Size{~0, ~0});
    } else if(name == "Super Famicom") {
      superFamicomSettings.construct(emulator);
      emulatorSettingsContainer.append(superFamicomSettings, Size{~0, ~0});
    } else if(name == "Nintendo 64") {
      emulatorSettingsContainer.append(n64Settings, Size{~0, ~0});
      n64Settings.construct(emulator);
    } else if(name == "Nintendo 64DD") {
      n64DDSettings.construct(emulator);
      emulatorSettingsContainer.append(n64DDSettings, Size{~0, ~0});
    } else if(name == "Game Boy Advance") {
      gameBoyAdvanceSettings.construct(emulator);
      emulatorSettingsContainer.append(gameBoyAdvanceSettings, Size{~0, ~0});
    } else if(name == "Game Boy") {
      gameBoySettings.construct(emulator);
      emulatorSettingsContainer.append(gameBoySettings, Size{~0, ~0});
    } else if(name == "Game Boy Color") {
      gameBoyColorSettings.construct(emulator);
      emulatorSettingsContainer.append(gameBoyColorSettings, Size{~0, ~0});
    } else if(name == "Game Gear") {
      gameGearSettings.construct(emulator);
      emulatorSettingsContainer.append(gameGearSettings, Size{~0, ~0});
    } else if(name == "SG-1000") {
      sg1000Settings.construct(emulator);
      emulatorSettingsContainer.append(sg1000Settings, Size{~0, ~0});
    } else if(name == "SC-3000") {
      sc3000Settings.construct(emulator);
      emulatorSettingsContainer.append(sc3000Settings, Size{~0, ~0});
    } else if(name == "Master System") {
      masterSystemSettings.construct(emulator);
      emulatorSettingsContainer.append(masterSystemSettings, Size{~0, ~0});
    } else if(name == "Mega Drive") {
      megaDriveSettings.construct(emulator);
      emulatorSettingsContainer.append(megaDriveSettings, Size{~0, ~0});
    } else if(name == "Mega CD") {
      megaCDSettings.construct(emulator);
      emulatorSettingsContainer.append(megaCDSettings, Size{~0, ~0});
    } else if(name == "Mega 32X") {
      mega32XSettings.construct(emulator);
      emulatorSettingsContainer.append(mega32XSettings, Size{~0, ~0});
    } else if(name == "Mega CD 32X") {
      megaCD32XSettings.construct(emulator);
      emulatorSettingsContainer.append(megaCD32XSettings, Size{~0, ~0});
    } else if(name == "LaserActive (Sega PAC)") {
      megaLDSettings.construct(emulator);
      emulatorSettingsContainer.append(megaLDSettings, Size{~0, ~0});
    } else if(name == "Neo Geo AES") {
      neoGeoSettings.construct(emulator);
      emulatorSettingsContainer.append(neoGeoSettings, Size{~0, ~0});
    } else if(name == "Neo Geo Pocket") {
      neoGeoPocketSettings.construct(emulator);
      emulatorSettingsContainer.append(neoGeoPocketSettings, Size{~0, ~0});
    } else if(name == "Neo Geo Pocket Color") {
      neoGeoPocketColorSettings.construct(emulator);
      emulatorSettingsContainer.append(neoGeoPocketColorSettings, Size{~0, ~0});
    } else if(name == "PlayStation") {
      playStationSettings.construct(emulator);
      emulatorSettingsContainer.append(playStationSettings, Size{~0, ~0});
    } else if(name == "ZX Spectrum") {
      zxSpectrumSettings.construct(emulator);
      emulatorSettingsContainer.append(zxSpectrumSettings, Size{~0, ~0});
    } else if(name == "ZX Spectrum 128") {
      zxSpectrum128Settings.construct(emulator);
      emulatorSettingsContainer.append(zxSpectrum128Settings, Size{~0, ~0});
    }
    TableViewItem item{&emulatorList};
    item.setAttribute<std::shared_ptr<Emulator>>("emulator", emulator);
    TableViewCell cellName{&item};
    cellName.setText(emulator->name);
    TableViewCell manufacturer{&item};
    manufacturer.setAttribute<std::shared_ptr<Emulator>>("emulator", emulator);
    manufacturer.setText(emulator->manufacturer);
  }
  emulatorList.resizeColumns();
  emulatorList.column(0).setWidth(140_sx);
  emulatorList.column(1).setWidth(75_sx);
  eventChange();
}

auto EmulatorSettings::eventChange() -> void {
  homePanel.setVisible(false);
  systemInputSettings.setVisible(false);
  arcadeSettings.setVisible(false);
  a2600Settings.setVisible(false);
  wonderSwanSettings.setVisible(false);
  wonderSwanColorSettings.setVisible(false);
  pocketChallengeV2Settings.setVisible(false);
  colecoVisionSettings.setVisible(false);
  myVisionSettings.setVisible(false);
  msxSettings.setVisible(false);
  msx2Settings.setVisible(false);
  pcEngineSettings.setVisible(false);
  pcEngineCDSettings.setVisible(false);
  necPACSettings.setVisible(false);
  superGrafxSettings.setVisible(false);
  superGrafxCDSettings.setVisible(false);
  famicomSettings.setVisible(false);
  famicomDiskSystemSettings.setVisible(false);
  superFamicomSettings.setVisible(false);
  n64Settings.setVisible(false);
  n64DDSettings.setVisible(false);
  gameBoyAdvanceSettings.setVisible(false);
  gameBoySettings.setVisible(false);
  gameBoyColorSettings.setVisible(false);
  gameGearSettings.setVisible(false);
  sg1000Settings.setVisible(false);
  sc3000Settings.setVisible(false);
  masterSystemSettings.setVisible(false);
  megaDriveSettings.setVisible(false);
  megaCDSettings.setVisible(false);
  mega32XSettings.setVisible(false);
  megaCD32XSettings.setVisible(false);
  megaLDSettings.setVisible(false);
  neoGeoSettings.setVisible(false);
  neoGeoPocketSettings.setVisible(false);
  neoGeoPocketColorSettings.setVisible(false);
  playStationSettings.setVisible(false);
  zxSpectrumSettings.setVisible(false);
  zxSpectrum128Settings.setVisible(false);

  bool found = false;
  auto item = emulatorList.selected();
  VerticalLayout settingsToShow;
  if(auto emulator = item.attribute<std::shared_ptr<Emulator>>("emulator")) {
    emulatorTabFrame.setVisible();
    if(emulatorTabFrame.selected().text() == "System Settings") {
      auto name = emulator->name;
      if(name == "Arcade") found = true, settingsToShow = arcadeSettings;
      if(name == "Atari 2600") found = true, settingsToShow = a2600Settings;
      if(name == "WonderSwan") found = true, settingsToShow = wonderSwanSettings;
      if(name == "WonderSwan Color") found = true, settingsToShow = wonderSwanColorSettings;
      if(name == "Pocket Challenge V2") found = true, settingsToShow = pocketChallengeV2Settings;
      if(name == "ColecoVision") found = true, settingsToShow = colecoVisionSettings;
      if(name == "MyVisions") found = true, settingsToShow = myVisionSettings;
      if(name == "MSX") found = true, settingsToShow = msxSettings;
      if(name == "MSX2") found = true, settingsToShow = msx2Settings;
      if(name == "PC Engine") found = true, settingsToShow = pcEngineSettings;
      if(name == "PC Engine CD") found = true, settingsToShow = pcEngineCDSettings;
      if(name == "LaserActive (NEC PAC)") found = true, settingsToShow = necPACSettings;
      if(name == "SuperGrafx") found = true, settingsToShow = superGrafxSettings;
      if(name == "SuperGrafx CD") found = true, settingsToShow = superGrafxCDSettings;
      if(name == "Famicom") found = true, settingsToShow = famicomSettings;
      if(name == "Famicom Disk System") found = true, settingsToShow = famicomDiskSystemSettings;
      if(name == "Super Famicom") found = true, settingsToShow = superFamicomSettings;
      if(name == "Nintendo 64") found = true, settingsToShow = n64Settings;
      if(name == "Nintendo 64DD") found = true, settingsToShow = n64DDSettings;
      if(name == "Game Boy Advance") found = true, settingsToShow = gameBoyAdvanceSettings;
      if(name == "Game Boy") found = true, settingsToShow = gameBoySettings;
      if(name == "Game Boy Color") found = true, settingsToShow = gameBoyColorSettings;
      if(name == "Game Gear") found = true, settingsToShow = gameGearSettings;
      if(name == "SG-1000") found = true, settingsToShow = sg1000Settings;
      if(name == "SC-3000") found = true, settingsToShow = sc3000Settings;
      if(name == "Master System") found = true, settingsToShow = masterSystemSettings;
      if(name == "Mega Drive") found = true, settingsToShow = megaDriveSettings;
      if(name == "Mega CD") found = true, settingsToShow = megaCDSettings;
      if(name == "Mega 32X") found = true, settingsToShow = mega32XSettings;
      if(name == "Mega CD 32X") found = true, settingsToShow = megaCD32XSettings;
      if(name == "LaserActive (Sega PAC)") found = true, settingsToShow = megaLDSettings;
      if(name == "Neo Geo") found = true, settingsToShow = neoGeoSettings;
      if(name == "Neo Geo Pocket") found = true, settingsToShow = neoGeoPocketSettings;
      if(name == "Neo Geo Pocket Color") found = true, settingsToShow = neoGeoPocketColorSettings;
      if(name == "PlayStation") found = true, settingsToShow = playStationSettings;
      if(name == "ZX Spectrum") found = true, settingsToShow = zxSpectrumSettings;
      if(name == "ZX Spectrum 128") found = true, settingsToShow = zxSpectrum128Settings;
    }
    if(emulatorTabFrame.selected().text() == "System Settings" && found == true) {
      settingsToShow.setVisible();
    } else {
      systemInputSettings.systemChange(emulator);
      systemInputSettings.setVisible();
    }
  } else {
    emulatorTabFrame.setCollapsible();
    emulatorTabFrame.setVisible(false);
    homePanel.setVisible();
  }
  emulatorSettingsContainer.resize();
}

auto EmulatorSettings::eventToggle(TableViewCell cell) -> void {
  if(auto emulator = cell.attribute<std::shared_ptr<Emulator>>("emulator")) {
    emulator->configuration.visible = cell.checked();
    presentation.loadEmulators();
  }
}

/// MARK: MD settings

auto MegaDriveSettings::construct(std::shared_ptr<Emulator> emulator) -> void {
  setCollapsible();
  megaDriveTmssOption.setText("TMSS Boot Rom").setChecked(settings.megaDrive->system.tmss).onToggle([&] {
    settings.megaDrive->system.tmss = megaDriveTmssOption.checked();
  });
  megaDriveTmssLayout.setAlignment(1).setPadding(12_sx, 0);
  megaDriveTmssHint.setText("Enable/Disable the TMSS Boot Rom at system initialization").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}

/// MARK: MD 32X settings

auto Mega32XSettings::construct(std::shared_ptr<Emulator> emulator) -> void {
  setCollapsible();
  forceInterpreterLabel.setText("Force Interpreter:");
  forceInterpreterCheck.setText("Use interpreter instead of recompiler (slow)")
    .setChecked(settings.general.forceInterpreter).onToggle([&] {
      auto list = system->settingsOverridesList;
      if(std::find(list.begin(), list.end(), string{"Force Interpreter"}) == list.end()) {
        system->settingsOverridesList.push_back(string{"Force Interpreter"});
      }
      system->settingsOverrides->general.forceInterpreter = forceInterpreterCheck.checked();
    });
}


/// MARK: N64 settings

auto N64SettingsLayout::construct(std::shared_ptr<Emulator> emulator) -> void {
  setCollapsible();
  
  renderSettingsLabel.setText("Rendering Settings").setFont(Font().setBold());

  nintendo64SettingsLayout.setSize({2, 7}); // padding
  nintendo64SettingsLayout.setPadding(12_sx, 0);
  nintendo64SettingsLayout.column(0).setAlignment(1.0);
  nintendo64RenderSettingsLayout.setSize({2, 5});
  nintendo64RenderSettingsLayout.setPadding(12_sx, 0);
  nintendo64RenderSettingsLayout.column(0).setAlignment(1.0);

  homebrewLabel.setText("Homebrew Mode:");
  homebrewCheck.setText("Activate core-specific features to help homebrew developers")
    .setChecked(settings.general.homebrewMode).onToggle([&] {
      //todo
      settings.general.homebrewMode = homebrewCheck.checked();
  });

  forceInterpreterLabel.setText("Interpreter:");
  forceInterpreterCheck.setText("Use interpreter instead of recompiler (slow)")
    .setChecked(settings.general.forceInterpreter).onToggle([&] {
      //todo
      settings.general.forceInterpreter = forceInterpreterCheck.checked();
  });

  disableVideoInterfaceProcessingLabel.setText("Disable VI Processing:");
  disableVideoInterfaceProcessingCheck.setText("Render image from VRAM directly, bypassing the Video Interface").setChecked(settings.nintendo64->video.disableVideoInterfaceProcessing).onToggle([&] {
    settings.nintendo64->video.disableVideoInterfaceProcessing = disableVideoInterfaceProcessingCheck.checked();
    if(emulator) emulator->setBoolean("Disable Video Interface Processing", settings.nintendo64->video.disableVideoInterfaceProcessing);
  });

  weaveDeinterlacingLabel.setText("Weave Deinterlacing:");
  weaveDeinterlacingCheck.setText("Doubles the perceived vertical resolution; incompatible with supersampling").setChecked(settings.nintendo64->video.weaveDeinterlacing).onToggle([&] {
    settings.nintendo64->video.weaveDeinterlacing = weaveDeinterlacingCheck.checked();
    if(emulator) emulator->setBoolean("(Experimental) Double the perceived vertical resolution; disabled when supersampling is used", settings.nintendo64->video.weaveDeinterlacing);
    if(weaveDeinterlacingCheck.checked() == true) {
      renderSupersamplingCheck.setChecked(false).setEnabled(false);
      settings.nintendo64->video.supersampling = false;
    } else {
      if(settings.nintendo64->video.quality != "Native") renderSupersamplingCheck.setEnabled(true);
    }
  });
  renderQualityLabel.setText("Render resolution:");
  ComboButtonItem renderQualityNative{&renderQualityOption};
  renderQualityNative.setText("Native");
  ComboButtonItem renderQuality2xNative{&renderQualityOption};
  renderQuality2xNative.setText("2x Native");
  ComboButtonItem renderQuality4xNative{&renderQualityOption};
  renderQuality4xNative.setText("4x Native");
  renderQualityOption.onChange([&] {
    auto idx = renderQualityOption.selected();
    auto value = idx.text();
    if (value != settings.nintendo64->video.quality) {
      settings.nintendo64->video.quality = value;

      if (value == "Native") {
        settings.nintendo64->video.quality = "Native";
        renderSupersamplingCheck.setChecked(false).setEnabled(false);
        settings.nintendo64->video.supersampling = false;
        weaveDeinterlacingCheck.setEnabled(true);
      } else if (value == "2x Native") {
        settings.nintendo64->video.quality = "2x Native";
        if(weaveDeinterlacingCheck.checked() == false) renderSupersamplingCheck.setChecked(settings.nintendo64->video.supersampling).setEnabled(true);
      } else if (value == "4x Native") {
        settings.nintendo64->video.quality = "4x Native";
        if(weaveDeinterlacingCheck.checked() == false) renderSupersamplingCheck.setChecked(settings.nintendo64->video.supersampling).setEnabled(true);
      }
    }
  });
  if(settings.nintendo64->video.quality == "Native") renderQualityNative.setSelected();
  if(settings.nintendo64->video.quality == "2x Native") renderQuality2xNative.setSelected();
  if(settings.nintendo64->video.quality == "4x Native") renderQuality4xNative.setSelected();
  renderSupersamplingLabel.setText("Supersampling:");
  renderSupersamplingCheck.setText("Scale 2x and 4x resolutions back down to native").setChecked(settings.nintendo64->video.supersampling && settings.nintendo64->video.quality != "Native").setEnabled(settings.nintendo64->video.quality != "Native").onToggle([&] {
    settings.nintendo64->video.supersampling = renderSupersamplingCheck.checked();
    if(renderSupersamplingCheck.checked() == true) {
      weaveDeinterlacingCheck.setEnabled(false).setChecked(false);
      settings.nintendo64->video.weaveDeinterlacing = false;
    } else {
      weaveDeinterlacingCheck.setEnabled(true);
    }
  });
  //wipe settings
  renderSettingsHint.setText("Note: Rendering settings changes require a system reload to take effect").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  #if !defined(VULKAN)
  //hide Vulkan-specific options if Vulkan is not available
  renderSettingsLabel.setCollapsible(true).setVisible(false);
  renderQualityLayout.setCollapsible(true).setVisible(false);
  renderSupersamplingLayout.setCollapsible(true).setVisible(false);
  renderSettingsHint.setCollapsible(true).setVisible(false);
  disableVideoInterfaceProcessingLayout.setCollapsible(true).setVisible(false);
  weaveDeinterlacingLayout.setCollapsible(true).setVisible(false);
  #endif
  
  nintendo64SettingsLabel.setText("").setFont(Font().setBold());

  expansionPakCheck.setText("Enable the 4MB Expansion Pak").setChecked(settings.nintendo64->system.expansionPak).onToggle([&] {
    settings.nintendo64->system.expansionPak = expansionPakCheck.checked();
  });
  expansionPakLabel.setText("Expansion Pak:");

  for (auto& opt : array<string[4]>{"32KiB (Default)", "128KiB (Datel 1Meg)", "512KiB (Datel 4Meg)", "1984KiB (Maximum)"}) {
    ComboButtonItem item{&controllerPakBankOption};
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
  controllerPakBankOption.onChange([&] {
    auto idx = controllerPakBankOption.selected();
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
  controllerPakBankLabel.setText("Controller Pak Size:");
}

auto ArcadeSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto A2600Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto ColecoVisionSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto FamicomSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto FamicomDiskSystemSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto GameBoyAdvanceSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto GameBoySettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto GameBoyColorSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto GameGearSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MasterSystemSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MegaCDSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MegaCD32XSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MegaLDSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MSXSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MSX2Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto MyVisionSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoPocketSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoPocketColorSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto N64DDSettingsLayout::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto PCEngineSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto PCEngineCDSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto NECPACSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto PlayStationSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto PocketChallengeV2Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto SaturnSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto SG1000Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto SC3000Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}

// MARK: SFC settings
auto SuperFamicomSettings::construct(std::shared_ptr<Emulator> emulator) -> void {
  setCollapsible();
  colorBleedHint.setText("Color Bleed:");
  colorBleedOption.setText("Blur adjacent pixels for translucency effects").setChecked(settings.video.colorBleed).onToggle([&] {
    settings.video.colorBleed = colorBleedOption.checked();
    if(emulator) emulator->setColorBleed(settings.video.colorBleed);
  });
  sfcRenderSettingsLayout.setSize({2, 2});
}

auto SuperGrafxSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto SuperGrafxCDSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto WonderSwanSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto WonderSwanColorSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto ZXSpectrumSettings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
auto ZXSpectrum128Settings::construct(std::shared_ptr<Emulator> emulator) -> void {setCollapsible();}
