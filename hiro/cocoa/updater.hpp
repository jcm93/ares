#if defined(Hiro_Updater)
#import <Sparkle/Sparkle.h>

@interface CocoaUpdater : NSObject <SPUUpdaterDelegate> {
@public
  hiro::mUpdater* updater;
  SPUStandardUpdaterController *updaterController;
}
-(void) checkForUpdates;
-(id) initWith:(hiro::mUpdater&)updater;

@end

namespace hiro {

struct pUpdater : pObject {
  Declare(Updater, Object)

  auto setEnabled(bool enabled) -> void override;
  auto checkForUpdates() -> void;

  CocoaUpdater* cocoaUpdater = nullptr;
};

}

#endif
