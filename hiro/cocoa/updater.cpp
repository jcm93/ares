#if defined(Hiro_Updater)
@implementation CocoaUpdater

- (void)checkForUpdates {
  [updaterController checkForUpdates:nil];
}

-(id) initWith:(hiro::mUpdater&)updaterReference {
  if(self = [super init]) {
    updater = &updaterReference;
    updaterController = [[SPUStandardUpdaterController alloc] initWithStartingUpdater:YES updaterDelegate:self userDriverDelegate:nil];
  }
  return self;
}

@end

namespace hiro {

  auto pUpdater::setEnabled(bool enabled) -> void {
  }

  auto pUpdater::checkForUpdates() -> void {
    return [cocoaUpdater checkForUpdates];
  }

}
#endif
