auto VideoSettings::videoRefresh() -> void {
  videoDriverList.reset();
  for(auto& driver : ruby::video.hasDrivers()) {
    ComboButtonItem item{&videoDriverList};
    item.setText(driver);
    if(driver == ruby::video.driver()) item.setSelected();
    if(settings.video.driver == ruby::video.driver()) {
      videoDriverAssign.setEnabled(false);
    }
  }
  videoMonitorList.reset();
  for(auto& monitor : ruby::video.hasMonitors()) {
    ComboButtonItem item{&videoMonitorList};
    item.setText(monitor.name);
    if(monitor.name == ruby::video.monitor()) item.setSelected();
  }
  videoFormatList.reset();
  for(auto& format : ruby::video.hasFormats()) {
    ComboButtonItem item{&videoFormatList};
    item.setText(format);
    if(format == ruby::video.format()) item.setSelected();
  }
  videoMonitorList.setEnabled(videoMonitorList.itemCount() > 1 && ruby::video.hasMonitor());
  videoFormatList.setEnabled(0 && videoFormatList.itemCount() > 1);
#if !defined(PLATFORM_MACOS)
  videoExclusiveToggle.setChecked(ruby::video.exclusive()).setEnabled(ruby::video.hasExclusive());
#endif
#if defined(PLATFORM_MACOS)
  videoColorSpaceToggle.setChecked(ruby::video.forceSRGB()).setEnabled(ruby::video.hasForceSRGB());
  videoThreadedRendererToggle.setChecked(ruby::video.threadedRenderer()).setEnabled(ruby::video.hasThreadedRenderer());
  videoNativeFullScreenToggle.setChecked(ruby::video.nativeFullScreen()).setEnabled(ruby::video.hasNativeFullScreen());
#endif
  VerticalLayout::resize();
}

auto VideoSettings::videoDriverUpdate() -> bool {
  if(emulator && settings.video.driver != "None" && MessageDialog(
    "Warning: incompatible drivers may cause this software to crash.\n"
    "Are you sure you want to change this driver while a game is loaded?"
  ).setAlignment(settingsWindow).question() != "Yes") return false;
  program.videoDriverUpdate();
  videoRefresh();
  return true;
}

auto VideoSettings::construct() -> void {
  setCollapsible();
  setVisible(false);
  
  videoLabel.setText("Video").setFont(Font().setBold());
  videoDriverList.onChange([&] {
    bool enabled = false;
    if(videoDriverList.selected().text() != settings.video.driver) { enabled = true; }
    videoDriverAssign.setEnabled(enabled);
  });
  videoDriverLabel.setText("Driver:");
  videoDriverAssign.setText("Apply").setEnabled(false).onActivate([&] {
    settings.video.driver = videoDriverList.selected().text();
    if (videoDriverUpdate()) {
      videoDriverAssign.setEnabled(false);
    }
  });
  videoMonitorLabel.setText("Fullscreen monitor:");
  videoMonitorList.onChange([&] {
    settings.video.monitor = videoMonitorList.selected().text();
    program.videoMonitorUpdate();
    videoRefresh();
  });
  videoFormatLabel.setText("Format:");
  videoFormatList.onChange([&] {
    settings.video.format = videoFormatList.selected().text();
    program.videoFormatUpdate();
    videoRefresh();
  });
#if !defined(PLATFORM_MACOS)
  videoExclusiveToggle.setText("Exclusive mode").onToggle([&] {
    settings.video.exclusive = videoExclusiveToggle.checked();
    ruby::video.setExclusive(settings.video.exclusive);
  });
#endif
#if defined(PLATFORM_MACOS)
  videoColorSpaceToggle.setText("Force sRGB").onToggle([&] {
    settings.video.forceSRGB = videoColorSpaceToggle.checked();
    ruby::video.setForceSRGB(settings.video.forceSRGB);
  });
  videoThreadedRendererToggle.setText("Threaded").onToggle([&] {
    settings.video.threadedRenderer = videoThreadedRendererToggle.checked();
    ruby::video.setThreadedRenderer(settings.video.threadedRenderer);
  });
  videoNativeFullScreenToggle.setText("Use native fullscreen").onToggle([&] {
    settings.video.nativeFullScreen = videoNativeFullScreenToggle.checked();
    ruby::video.setNativeFullScreen(settings.video.nativeFullScreen);
    videoRefresh();
  });
#endif
  
  videoDriverLayout.setPadding(12_sx, 0);
  videoPropertyLayout.setPadding(12_sx, 0);
  videoToggleLayout.setPadding(12_sx, 0);

  colorAdjustmentLabel.setText("Color Adjustment").setFont(Font().setBold());
  colorAdjustmentLayout.setSize({3, 3}).setPadding(12_sx, 0);
  colorAdjustmentLayout.column(0).setAlignment(1.0);

  luminanceLabel.setText("Luminance:");
  luminanceValue.setAlignment(0.5);
  luminanceSlider.setLength(101).setPosition(settings.video.luminance * 100.0).onChange([&] {
    settings.video.luminance = luminanceSlider.position() / 100.0;
    luminanceValue.setText({luminanceSlider.position(), "%"});
    program.paletteUpdate();
  }).doChange();

  saturationLabel.setText("Saturation:");
  saturationValue.setAlignment(0.5);
  saturationSlider.setLength(201).setPosition(settings.video.saturation * 100.0).onChange([&] {
    settings.video.saturation = saturationSlider.position() / 100.0;
    saturationValue.setText({saturationSlider.position(), "%"});
    program.paletteUpdate();
  }).doChange();

  gammaLabel.setText("Gamma:");
  gammaValue.setAlignment(0.5);
  gammaSlider.setLength(101).setPosition((settings.video.gamma - 1.0) * 100.0).onChange([&] {
    settings.video.gamma = 1.0 + gammaSlider.position() / 100.0;
    gammaValue.setText({100 + gammaSlider.position(), "%"});
    program.paletteUpdate();
  }).doChange();

  
}
