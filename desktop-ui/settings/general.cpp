
auto GeneralSettings::construct() -> void {
  setCollapsible();
  commonSettingsLabel.setText("System Options").setFont(Font().setBold());
  commonSettingsHint.setText("These options may be overridden for particular systems in Emulators settings.").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  systemOptionsTableLayout.setSize({2, 7}).setPadding(12_sx, 0);
  systemOptionsTableLayout.column(0).setAlignment(1.0);

  rewindHint.setText("Rewind:");
  rewind.setText("Allow you to reverse time via the rewind hotkey").setChecked(settings.general.rewind).onToggle([&] {
    settings.general.rewind = rewind.checked();
    program.rewindReset();
  }).doToggle();

  runAheadHint.setText("Run-Ahead:");
  runAhead.setText("Remove one frame of input lag, but double system requirements")
    .setEnabled(co_serializable()).setChecked(settings.general.runAhead && co_serializable())
    .onToggle([&] {
    settings.general.runAhead = runAhead.checked() && co_serializable();
    program.runAheadUpdate();
  });

  autoSaveMemoryHint.setText("Auto-Save Memory:");
  autoSaveMemory.setText("Periodically auto-save to prevent game saves from being lost")
    .setChecked(settings.general.autoSaveMemory).onToggle([&] {
    settings.general.autoSaveMemory = autoSaveMemory.checked();
  });

  homebrewModeHint.setText("Homebrew Mode:");
  homebrewMode.setText("Activate core-specific features to help homebrew developers")
    .setChecked(settings.general.homebrewMode).onToggle([&] {
    settings.general.homebrewMode = homebrewMode.checked();
  });

  forceInterpreterHint.setText("Force Interpreter:");
  forceInterpreter.setText("(Slow) Enable interpreter for cores that default to a recompiler")
    .setChecked(settings.general.forceInterpreter).onToggle([&] {
    settings.general.forceInterpreter = forceInterpreter.checked();
  });

  syncLabel.setText("Synchronisation").setFont(Font().setBold());

  syncAdjustmentLayout.setSize({2, 5}).setPadding(12_sx, 0);
  syncAdjustmentLayout.column(0).setAlignment(1.0);

  syncDescriptionLabel.setText("Sync to:");
  syncDescriptionHintLayout.setPadding(12_sx, 0);

  ComboButtonItem audioItem{&syncOptionList};
  ComboButtonItem videoItem{&syncOptionList};
  ComboButtonItem dualItem{&syncOptionList};
  ComboButtonItem noneItem{&syncOptionList};
  audioItem.setText("Audio");
  videoItem.setText("Video");
  dualItem.setText("Dual (VRR or high refresh rate)");
  noneItem.setText("None");

  syncDescriptionHint.setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  //syncDescriptionHint.setEditable(false);

  syncOptionList.onChange([&] {
    auto selected = syncOptionList.selected();
    if(selected.text() == "Audio") {
      settings.audio.blocking = true;
      settings.video.blocking = false;
      settings.audio.dynamic = false;
    } else if(selected.text() == "Video") {
      settings.audio.blocking = false;
      settings.video.blocking = true;
      settings.audio.dynamic = true;
    } else if(selected.text() == "Dual (VRR or high refresh rate)") {
      settings.audio.blocking = true;
      settings.video.blocking = true;
      settings.audio.dynamic = false;
    } else {
      settings.audio.blocking = false;
      settings.video.blocking = false;
      settings.audio.dynamic = true;
    }
    ruby::video.setBlocking(settings.video.blocking);
    ruby::audio.setBlocking(settings.audio.blocking);
    ruby::audio.setDynamic(settings.audio.dynamic);
    refresh();
  });

  audioLatencyLabel.setText("Latency:");
  audioLatencyList.onChange([&] {
    settings.audio.latency = audioLatencyList.selected().text().split(" ").first().natural();
    program.audioLatencyUpdate();
    audioSettings.audioRefresh();
  });

  gpuSyncDescription.setText("GPU sync:");
  gpuSyncCheckLabel.setText("Block until the GPU has completed all rendering work");
  gpuSyncCheckLabel.onToggle([&] {
    settings.video.flush = gpuSyncCheckLabel.checked();
    ruby::video.setFlush(settings.video.flush);
  });

}

auto GeneralSettings::refresh() -> void {
  if(ruby::video.blocking() && ruby::audio.blocking()) {
    syncOptionList.item(2).setSelected();
    syncDescriptionHint.setText("The guest will synchronize with both host audio and host refresh rate.\nGenerally requires a VRR or high refresh rate display.");
  } else if(ruby::video.blocking()) {
    syncOptionList.item(1).setSelected();
    syncDescriptionHint.setText("The guest system will run in sync with host display refresh rate.\nAudio will speed up or slow down to match the running rate of the emulated system.");
  } else if(ruby::audio.blocking()) {
    syncOptionList.item(0).setSelected();
    syncDescriptionHint.setText("The guest system will run in sync with host audio playback.");
  } else {
    syncOptionList.item(3).setSelected();
    syncDescriptionHint.setText("The guest system will run at an unbounded rate.");
  }
  //TODO
  if(ruby::video.hasBlocking()) {

  } else {

  }
  if(ruby::audio.hasBlocking()) {

  } else {

  }
  gpuSyncCheckLabel.setChecked(ruby::video.flush()).setEnabled(ruby::video.hasFlush());
}

