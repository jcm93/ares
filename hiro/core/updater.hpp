#if defined(Hiro_Updater)
struct mUpdater : mObject {
  Declare(Updater)

  mUpdater();

  auto checkForUpdates() -> void;

//private:
  struct State {
    bool hasUpdate;
  } state;
};
#endif
