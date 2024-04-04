#include "../desktop-ui.hpp"
#include "platform.cpp"
#include "load.cpp"
#include "states.cpp"
#include "rewind.cpp"
#include "status.cpp"
#include "utility.cpp"
#include "drivers.cpp"
#if defined(PLATFORM_MACOS)
#include <dispatch/dispatch.h>
#endif

Program program;

auto Program::create() -> void {
  ares::platform = this;

  videoDriverUpdate();
  audioDriverUpdate();
  inputDriverUpdate();

  driverSettings.videoRefresh();
  driverSettings.audioRefresh();
  driverSettings.inputRefresh();

  if(startGameLoad) {
    auto gameToLoad = startGameLoad.takeFirst();
    if(startSystem) {
      for(auto &emulator: emulators) {
        if(emulator->name == startSystem) {
          if(load(emulator, gameToLoad)) {
            if(startFullScreen) videoFullScreenToggle();
          }
          return;
        }
      }
    }

    if(auto emulator = identify(gameToLoad)) {
      if(load(emulator, gameToLoad)) {
        if(startFullScreen) videoFullScreenToggle();
      }
    }
  }
}

auto Program::main() -> void {
  if(Application::modal()) {
    ruby::audio.clear();
    return;
  }

#if defined(PLATFORM_MACOS)
  dispatch_async(dispatch_get_main_queue(), ^(void){
#endif
    updateMessage();
#if defined(PLATFORM_MACOS)
  });
#endif
  inputManager.poll();
  inputManager.pollHotkeys();

  bool defocused = driverSettings.inputDefocusPause.checked() && !ruby::video.fullScreen() && !presentation.focused();
  if(emulator && defocused) message.text = "Paused";

  if(settings.debugServer.enabled) {
#if defined(PLATFORM_MACOS)
    dispatch_async(dispatch_get_main_queue(), ^(void){
#endif
      presentation.statusDebug.setText(
        nall::GDB::server.getStatusText(settings.debugServer.port, settings.debugServer.useIPv4)
      );
#if defined(PLATFORM_MACOS)
    });
#endif
  }

  if(emulator && nall::GDB::server.isHalted()) {
    ruby::audio.clear();
    nall::GDB::server.updateLoop(); // sleeps internally
    return;
  }

  if(!emulator || (paused && !program.requestFrameAdvance) || defocused || !loaded) {
    ruby::audio.clear();
    nall::GDB::server.updateLoop();
    usleep(20 * 1000);
    return;
  }

  rewindRun();

  nall::GDB::server.updateLoop();

  program.requestFrameAdvance = false;
  if(!runAhead || fastForwarding || rewinding) {
    emulator->root->run();
  } else {
    ares::setRunAhead(true);
    emulator->root->run();
    auto state = emulator->root->serialize(false);
    ares::setRunAhead(false);
    emulator->root->run();
    state.setReading();
    emulator->root->unserialize(state);
  }

  nall::GDB::server.updateLoop();

  if(settings.general.autoSaveMemory) {
    static u64 previousTime = chrono::timestamp();
    u64 currentTime = chrono::timestamp();
    if(currentTime - previousTime >= 30) {
      previousTime = currentTime;
      emulator->save();
    }
  }

  //if Platform::video() changed the screen resolution, resize the presentation window here.
  //window operations must be performed from the main thread.
  if(emulator->latch.changed) {
    emulator->latch.changed = false;
    if(settings.video.adaptiveSizing) {
#if defined(PLATFORM_MACOS)
      dispatch_async(dispatch_get_main_queue(), ^(void){
#endif
        presentation.resizeWindow();
#if defined(PLATFORM_MACOS)
      });
#endif
    }
  }
#if defined(PLATFORM_MACOS)
  dispatch_async(dispatch_get_main_queue(), ^(void){
#endif
    memoryEditor.liveRefresh();
    graphicsViewer.liveRefresh();
    propertiesViewer.liveRefresh();
#if defined(PLATFORM_MACOS)
  });
#endif
}

auto Program::quit() -> void {
  unload();
  Application::processEvents();
  Application::quit();

  ruby::video.reset();
  ruby::audio.reset();
  ruby::input.reset();
}
