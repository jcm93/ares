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
    item.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    TableViewCell cellName{&item};
    cellName.setText(emulator->name);
    TableViewCell manufacturer{&item};
    manufacturer.setAttribute<shared_pointer<Emulator>>("emulator", emulator);
    manufacturer.setText(emulator->manufacturer);
  }
  emulatorList.resizeColumns();
  emulatorList.column(0).setWidth(140_sx);
  emulatorList.column(1).setWidth(75_sx);
  eventChange();
}

auto EmulatorSettings::eventChange() -> void {
  homePanel.setVisible(false);
  overrideSettings.setVisible(false);
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
  if(auto emulator = item.attribute<shared_pointer<Emulator>>("emulator")) {
    emulatorTabFrame.setVisible();
    if(emulatorTabFrame.selected().text() == "System Settings") {
      auto name = emulator->name;
      if(name == "Arcade") found = true, arcadeSettings.setVisible(true);
      if(name == "Atari 2600") found = true, a2600Settings.setVisible(true);
      if(name == "WonderSwan") found = true, wonderSwanSettings.setVisible(true);
      if(name == "WonderSwan Color") found = true, wonderSwanColorSettings.setVisible(true);
      if(name == "Pocket Challenge V2") found = true, pocketChallengeV2Settings.setVisible(true);
      if(name == "ColecoVision") found = true, colecoVisionSettings.setVisible(true);
      if(name == "MyVisions") found = true, myVisionSettings.setVisible(true);
      if(name == "MSX") found = true, msxSettings.setVisible(true);
      if(name == "MSX2") found = true, msx2Settings.setVisible(true);
      if(name == "PC Engine") found = true, pcEngineSettings.setVisible(true);
      if(name == "PC Engine CD") found = true, pcEngineCDSettings.setVisible(true);
      if(name == "LaserActive (NEC PAC)") found = true, necPACSettings.setVisible(true);
      if(name == "SuperGrafx") found = true, superGrafxSettings.setVisible(true);
      if(name == "SuperGrafx CD") found = true, superGrafxCDSettings.setVisible(true);
      if(name == "Famicom") found = true, famicomSettings.setVisible(true);
      if(name == "Famicom Disk System") found = true, famicomDiskSystemSettings.setVisible(true);
      if(name == "Super Famicom") found = true, superFamicomSettings.setVisible(true);
      if(name == "Nintendo 64") found = true, n64Settings.setVisible(true);
      if(name == "Nintendo 64DD") found = true, n64DDSettings.setVisible(true);
      if(name == "Game Boy Advance") found = true, gameBoyAdvanceSettings.setVisible(true);
      if(name == "Game Boy") found = true, gameBoySettings.setVisible(true);
      if(name == "Game Boy Color") found = true, gameBoyColorSettings.setVisible(true);
      if(name == "Game Gear") found = true, gameGearSettings.setVisible(true);
      if(name == "SG-1000") found = true, sg1000Settings.setVisible(true);
      if(name == "SC-3000") found = true, sc3000Settings.setVisible(true);
      if(name == "Master System") found = true, masterSystemSettings.setVisible(true);
      if(name == "Mega Drive") found = true, megaDriveSettings.setVisible(true);
      if(name == "Mega CD") found = true, megaCDSettings.setVisible(true);
      if(name == "Mega 32X") found = true, mega32XSettings.setVisible(true);
      if(name == "Mega CD 32X") found = true, megaCD32XSettings.setVisible(true);
      if(name == "LaserActive (Sega PAC)") found = true, megaLDSettings.setVisible(true);
      if(name == "Neo Geo") found = true, neoGeoSettings.setVisible(true);
      if(name == "Neo Geo Pocket") found = true, neoGeoPocketSettings.setVisible(true);
      if(name == "Neo Geo Pocket Color") found = true, neoGeoPocketColorSettings.setVisible(true);
      if(name == "PlayStation") found = true, playStationSettings.setVisible(true);
      if(name == "ZX Spectrum") found = true, zxSpectrumSettings.setVisible(true);
      if(name == "ZX Spectrum 128") found = true, zxSpectrum128Settings.setVisible(true);
    } else if(emulatorTabFrame.selected().text() == "Input" && found == true) {
      overrideSettings.setVisible();
    }
  } else if(emulatorTabFrame.selected().text() == "Input" && found == true) {
    overrideSettings.setVisible();
  } else {
    emulatorTabFrame.setCollapsible();
    emulatorTabFrame.setVisible(false);
    homePanel.setVisible();
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

auto MegaDriveSettings::construct(shared_pointer<Emulator> emulator) -> void {
  setCollapsible();
  megaDriveTmssOption.setText("TMSS Boot Rom").setChecked(settings.megaDrive->system.tmss).onToggle([&] {
    settings.megaDrive->system.tmss = megaDriveTmssOption.checked();
  });
  megaDriveTmssLayout.setAlignment(1).setPadding(12_sx, 0);
  megaDriveTmssHint.setText("Enable/Disable the TMSS Boot Rom at system initialization").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
}

/// MARK: MD 32X settings

auto Mega32XSettings::construct(shared_pointer<Emulator> emulator) -> void {
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

auto N64SettingsLayout::construct(shared_pointer<Emulator> emulator) -> void {
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

auto ArcadeSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto A2600Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto ColecoVisionSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto FamicomSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto FamicomDiskSystemSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto GameBoyAdvanceSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto GameBoySettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto GameBoyColorSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto GameGearSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MasterSystemSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MegaCDSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MegaCD32XSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MegaLDSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MSXSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MSX2Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto MyVisionSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoPocketSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto NeoGeoPocketColorSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto N64DDSettingsLayout::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto PCEngineSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto PCEngineCDSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto NECPACSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto PlayStationSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto PocketChallengeV2Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto SaturnSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto SG1000Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto SC3000Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}

// MARK: SFC settings
auto SuperFamicomSettings::construct(shared_pointer<Emulator> emulator) -> void {
  setCollapsible();
  colorBleedHint.setText("Color Bleed:");
  colorBleedOption.setText("Blur adjacent pixels for translucency effects").setChecked(settings.video.colorBleed).onToggle([&] {
    settings.video.colorBleed = colorBleedOption.checked();
    if(emulator) emulator->setColorBleed(settings.video.colorBleed);
  });
  sfcRenderSettingsLayout.setSize({2, 2});
}

auto SuperGrafxSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto SuperGrafxCDSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto WonderSwanSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto WonderSwanColorSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto ZXSpectrumSettings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
auto ZXSpectrum128Settings::construct(shared_pointer<Emulator> emulator) -> void {setCollapsible();}
