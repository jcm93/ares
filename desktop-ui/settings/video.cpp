auto VideoSettings::videoRefresh() -> void {
  videoDriverList.reset();
  for(auto& driver : ruby::video.hasDrivers()) {
    ComboButtonItem item{&videoDriverList};
    item.setText(driver);
    if(driver == ruby::video.driver()) item.setSelected();
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
    if(videoDriverList.selected().text() != settings.video.driver) {
      auto old = settings.video.driver;
      settings.video.driver = videoDriverList.selected().text();
      if (!videoDriverUpdate()) {
        settings.video.driver = old;
        videoRefresh();
      }
    }
  });
  videoDriverLabel.setText("Backend:");
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
  videoExclusiveToggle.setText("Grant ares complete control over system video output").onToggle([&] {
    settings.video.exclusive = videoExclusiveToggle.checked();
    ruby::video.setExclusive(settings.video.exclusive);
  });
#endif
#if defined(PLATFORM_MACOS)
  videoColorSpaceToggleName.setText("Force sRGB:");
  videoColorSpaceToggle.setText("Render the final texture output in the sRGB color space").onToggle([&] {
    settings.video.forceSRGB = videoColorSpaceToggle.checked();
    ruby::video.setForceSRGB(settings.video.forceSRGB);
  });
  videoThreadedRendererToggleName.setText("Threaded:");
  videoThreadedRendererToggle.setText("Perform rendering in a dedicated thread").onToggle([&] {
    settings.video.threadedRenderer = videoThreadedRendererToggle.checked();
    ruby::video.setThreadedRenderer(settings.video.threadedRenderer);
  });
  videoNativeFullScreenToggleName.setText("Use native fullscreen:");
  videoNativeFullScreenToggle.setText("Disable to render around camera housing, or for use with bezel shaders.").onToggle([&] {
    settings.video.nativeFullScreen = videoNativeFullScreenToggle.checked();
    ruby::video.setNativeFullScreen(settings.video.nativeFullScreen);
    videoRefresh();
  });
  videoDriverLayout.setSize({2, 7});
#else
  videoDriverLayout.setSize({2, 5});
  videoExclusiveToggleName.setText("Exclusive mode:");
#endif

  videoDriverLayout.setPadding(12_sx, 0);
  videoDriverLayout.column(0).setAlignment(1.0);

  colorAdjustmentLabel.setText("Color Adjustment").setFont(Font().setBold());
  colorAdjustmentLayout.setSize({3, 5}).setPadding(12_sx, 0);
  colorAdjustmentLayout.column(0).setAlignment(1.0);

  // ugly hack, todo remove
  luminanceLabel.setText("                 Luminance:");
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

  renderingOptionsTableLayout.setSize({2, 4}).setPadding(12_sx, 0);
  renderingOptionsTableLayout.column(0).setAlignment(1.0);

  emulatorSettingsLabel.setText("Rendering Options").setFont(Font().setBold());
  colorBleedHint.setText("Color Bleed:");
  colorBleedOption.setText("Blur adjacent pixels for translucency effects").setChecked(settings.video.colorBleed).onToggle([&] {
    settings.video.colorBleed = colorBleedOption.checked();
    if(emulator) emulator->setColorBleed(settings.video.colorBleed);
  });
  /*colorEmulationHint.setText("Color Emulation:");
  colorEmulationOption.setText("Match colors to how they look on real hardware").setChecked(settings.video.colorEmulation).onToggle([&] {
    settings.video.colorEmulation = colorEmulationOption.checked();
    if(emulator) emulator->setBoolean("Color Emulation", settings.video.colorEmulation);
  });
  deepBlackBoostHint.setText("Deep Black Boost:");
  deepBlackBoostOption.setText("Apply a gamma ramp to crush black levels (SNES/SFC)").setChecked(settings.video.deepBlackBoost).onToggle([&] {
    settings.video.deepBlackBoost = deepBlackBoostOption.checked();
    if(emulator) emulator->setBoolean("Deep Black Boost", settings.video.deepBlackBoost);
  });*/
  interframeBlendingHint.setText("Interframe Blending:");
  interframeBlendingOption.setText("Emulate LCD translucency effects, but increase motion blur").setChecked(settings.video.interframeBlending).onToggle([&] {
    settings.video.interframeBlending = interframeBlendingOption.checked();
    if(emulator) emulator->setBoolean("Interframe Blending", settings.video.interframeBlending);
  });
  overscanHint.setText("Overscan:");
  overscanOption.setText("Display the full frame without cropping 'undesirable' borders").setChecked(settings.video.overscan).onToggle([&] {
    settings.video.overscan = overscanOption.checked();
    if(emulator) emulator->setOverscan(settings.video.overscan);
  });
  /*pixelAccuracyHint.setText("Pixel Accuracy Mode:");
  pixelAccuracyOption.setText("Use pixel-accurate emulation where available").setChecked(settings.video.pixelAccuracy).onToggle([&] {
    settings.video.pixelAccuracy = pixelAccuracyOption.checked();
    if(emulator) emulator->setBoolean("Pixel Accuracy", settings.video.pixelAccuracy);
  });*/

  
}
