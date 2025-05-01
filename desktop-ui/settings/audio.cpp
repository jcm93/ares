auto AudioSettings::audioRefresh() -> void {
  audioDriverList.reset();
  for(auto& driver : ruby::audio.hasDrivers()) {
    ComboButtonItem item{&audioDriverList};
    item.setText(driver);
    if(driver == ruby::audio.driver()) item.setSelected();
    if(settings.audio.driver == ruby::audio.driver()) {
      audioDriverAssign.setEnabled(false);
    }
  }
  audioDeviceList.reset();
  for(auto& device : ruby::audio.hasDevices()) {
    ComboButtonItem item{&audioDeviceList};
    item.setText(device);
    if(device == ruby::audio.device()) item.setSelected();
  }
  audioFrequencyList.reset();
  for(auto& frequency : ruby::audio.hasFrequencies()) {
    ComboButtonItem item{&audioFrequencyList};
    item.setText(frequency);
    if(frequency == ruby::audio.frequency()) item.setSelected();
  }
  audioLatencyList.reset();
  for(auto& latency : ruby::audio.hasLatencies()) {
    ComboButtonItem item{&audioLatencyList};
    item.setText(latency);
    if(latency == ruby::audio.latency()) item.setSelected();
  }
  audioDeviceList.setEnabled(audioDeviceList.itemCount() > 1);
  audioExclusiveToggle.setChecked(ruby::audio.exclusive()).setEnabled(ruby::audio.hasExclusive());
  audioBlockingToggle.setChecked(ruby::audio.blocking()).setEnabled(ruby::audio.hasBlocking());
  audioDynamicToggle.setChecked(ruby::audio.dynamic()).setEnabled(ruby::audio.hasDynamic());
  VerticalLayout::resize();
}

auto AudioSettings::audioDriverUpdate() -> bool {
  if(emulator && settings.audio.driver != "None" && MessageDialog(
    "Warning: incompatible drivers may cause this software to crash.\n"
    "Are you sure you want to change this driver while a game is loaded?"
  ).setAlignment(settingsWindow).question() != "Yes") return false;
  program.audioDriverUpdate();
  audioRefresh();
  return true;
}

auto AudioSettings::construct() -> void {
  setCollapsible();
  setVisible(false);
  
  audioLabel.setText("Audio").setFont(Font().setBold());
  audioDriverList.onChange([&] {
    bool enabled = false;
    if(audioDriverList.selected().text() != settings.audio.driver) { enabled = true; }
    audioDriverAssign.setEnabled(enabled);
  });
  audioDriverLabel.setText("Driver:");
  audioDriverAssign.setText("Apply").setEnabled(false).onActivate([&] {
    settings.audio.driver = audioDriverList.selected().text();
    if (audioDriverUpdate()) {
      audioDriverAssign.setEnabled(false);
    }
  });
  audioDeviceLabel.setText("Output device:");
  audioDeviceList.onChange([&] {
    settings.audio.device = audioDeviceList.selected().text();
    program.audioDeviceUpdate();
    audioRefresh();
  });
  audioFrequencyLabel.setText("Frequency:");
  audioFrequencyList.onChange([&] {
    settings.audio.frequency = audioFrequencyList.selected().text().natural();
    program.audioFrequencyUpdate();
    audioRefresh();
  });
  audioLatencyLabel.setText("Latency:");
  audioLatencyList.onChange([&] {
    settings.audio.latency = audioLatencyList.selected().text().natural();
    program.audioLatencyUpdate();
    audioRefresh();
  });
  audioExclusiveToggle.setText("Exclusive mode").onToggle([&] {
    settings.audio.exclusive = audioExclusiveToggle.checked();
    ruby::audio.setExclusive(settings.audio.exclusive);
  });
  audioBlockingToggle.setText("Synchronize").onToggle([&] {
    settings.audio.blocking = audioBlockingToggle.checked();
    ruby::audio.setBlocking(settings.audio.blocking);
  });
  audioDynamicToggle.setText("Dynamic rate").onToggle([&] {
    settings.audio.dynamic = audioDynamicToggle.checked();
    ruby::audio.setDynamic(settings.audio.dynamic);
  });

  effectsLabel.setText("Effects").setFont(Font().setBold());
  effectsLayout.setSize({3, 2}).setPadding(12_sx, 0);
  effectsLayout.column(0).setAlignment(1.0);

  volumeLabel.setText("Volume:");
  volumeValue.setAlignment(0.5);
  volumeSlider.setLength(201).setPosition(settings.audio.volume * 100.0).onChange([&] {
    settings.audio.volume = volumeSlider.position() / 100.0;
    volumeValue.setText({volumeSlider.position(), "%"});
  }).doChange();

  balanceLabel.setText("Balance:");
  balanceValue.setAlignment(0.5);
  balanceSlider.setLength(101).setPosition((settings.audio.balance * 50.0) + 50.0).onChange([&] {
    settings.audio.balance = ((s32)balanceSlider.position() - 50.0) / 50.0;
    balanceValue.setText({balanceSlider.position(), "%"});
  }).doChange();
  
  audioDriverLayout.setPadding(12_sx, 0);
  audioDeviceLayout.setPadding(12_sx, 0);
  audioPropertyLayout.setPadding(12_sx, 0);
  audioToggleLayout.setPadding(12_sx, 0);
}
