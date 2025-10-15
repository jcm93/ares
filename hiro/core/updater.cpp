#if defined(Hiro_Updater)

mUpdater::mUpdater() {
  mObject::state.enabled = false;
}

auto mUpdater::allocate() -> pObject* {
  return new pUpdater(*this);
}

auto mUpdater::checkForUpdates() -> void {
  signal(checkForUpdates);
}

#endif
