auto SyncSettings::construct() -> void {
  setCollapsible();
  setVisible(false);
  
  syncLabel.setText("Synchronisation").setFont(Font().setBold());
  
  syncAdjustmentLayout.setSize({2, 6}).setPadding(12_sx, 0);
  syncAdjustmentLayout.column(0).setAlignment(1.0);
  
  syncDescriptionLabel.setText("Sync to:");
  syncDescriptionHintLayout.setPadding(12_sx, 0);
  
  ComboButtonItem audioItem{&syncOptionList};
  ComboButtonItem videoItem{&syncOptionList};
  ComboButtonItem dualItem{&syncOptionList};
  audioItem.setText("Audio");
  videoItem.setText("Video");
  dualItem.setText("Dual (VRR or high refresh rate)");
  
  syncDescriptionHint.setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  //syncDescriptionHint.setEditable(false);
  
  syncOptionList.onChange([&] {
    auto selected = syncOptionList.selected();
    if(selected.text() == "Audio") {
      settings.audio.blocking = true;
      settings.video.blocking = false;
    } else if(selected.text() == "Video") {
      settings.audio.blocking = false;
      settings.video.blocking = true;
    } else if(selected.text() == "Dual (VRR or high refresh rate)") {
      settings.audio.blocking = true;
      settings.video.blocking = true;
    }
    ruby::video.setBlocking(settings.video.blocking);
    ruby::audio.setBlocking(settings.audio.blocking);
    refresh();
  });

  gpuSyncDescription.setText("GPU sync:");
  gpuSyncCheckLabel.setText("Block until the GPU has completed all rendering work");
  gpuSyncCheckLabel.onToggle([&] {
    settings.video.flush = gpuSyncCheckLabel.checked();
    ruby::video.setFlush(settings.video.flush);
  });

  dynamicRateDescription.setText("Dynamic rate audio:");
  dynamicRateCheckLabel.setText("Audio will speed up or slow down to match the running rate of the emulated system");
  dynamicRateCheckLabel.onToggle([&] {
    settings.audio.dynamic = dynamicRateCheckLabel.checked();
    ruby::audio.setDynamic(settings.audio.dynamic);
  });
}

auto SyncSettings::refresh() -> void {
  if(ruby::video.blocking() && ruby::audio.blocking()) {
    syncOptionList.item(2).setSelected();
    syncDescriptionHint.setText("The guest will synchronize to both host audio and host refresh rate.\nGenerally requires a VRR or high refresh rate display.");
  } else if(ruby::video.blocking()) {
    syncOptionList.item(1).setSelected();
    syncDescriptionHint.setText("The guest system will run in sync with host display refresh rate.");
  } else if(ruby::audio.blocking()) {
    syncOptionList.item(0).setSelected();
    syncDescriptionHint.setText("The guest system will run in sync with host audio playback.");
  }
  //TODO
  if(ruby::video.hasBlocking()) {
    
  } else {
    
  }
  if(ruby::audio.hasBlocking()) {
    
  } else {
    
  }
  dynamicRateCheckLabel.setChecked(ruby::audio.dynamic()).setEnabled(ruby::audio.hasDynamic());
  gpuSyncCheckLabel.setChecked(ruby::video.flush()).setEnabled(ruby::video.hasFlush());
}
