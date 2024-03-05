//
//  metal.cpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include "metal/metal.hpp"

struct VideoMetal;

@interface RubyVideoMetal : MTKView {
@public
  VideoMetal* video;
}
-(id) initWith:(VideoMetal*)video pixelFormat:(MTLPixelFormat*)pixelFormat;
-(void) reshape;
-(BOOL) acceptsFirstResponder;
@end

@interface RubyWindowMetal : NSWindow <NSWindowDelegate> {
@public
  VideoMetal* video;
}
-(id) initWith:(VideoMetal*)video;
-(BOOL) canBecomeKeyWindow;
-(BOOL) canBecomeMainWindow;
@end

struct VideoMetal : VideoDriver, Metal {
  VideoMetal& self = *this;
  VideoMetal(Video& super) : VideoDriver(super) {}
  ~VideoMetal() { terminate(); }

  auto create() -> bool override {
    return initialize();
  }

  auto driver() -> string override { return "Metal"; }
  auto ready() -> bool override { return _ready; }

  auto hasFullScreen() -> bool override { return true; }
  auto hasContext() -> bool override { return true; }
  auto hasBlocking() -> bool override { return true; }
  auto hasFlush() -> bool override { return true; }
  auto hasShader() -> bool override { return true; }

  auto setFullScreen(bool fullScreen) -> bool override {
    return initialize();
  }

  auto setContext(uintptr context) -> bool override {
    return initialize();
  }

  auto setBlocking(bool blocking) -> bool override {
    return true;
  }

  auto setFlush(bool flush) -> bool override {
    return true;
  }

  auto setShader(string shader) -> bool override {
    return true;
  }

  auto focused() -> bool override {
    return true;
  }

  auto clear() -> void override {
    Metal::clear();
  }

  auto size(u32& width, u32& height) -> void override {
    auto area = [view convertRectToBacking:[view bounds]];
    width = area.size.width;
    height = area.size.height;
  }

  auto acquire(u32*& data, u32& pitch, u32 width, u32 height) -> bool override {
  }

  auto release() -> void override {
  }

  auto output(u32 width, u32 height) -> void override {
    /*lock_guard<recursive_mutex> lock(mutex);
    acquireContext();
    u32 windowWidth, windowHeight;
    size(windowWidth, windowHeight);

    if([view lockFocusIfCanDraw]) {
      OpenGL::absoluteWidth = width;
      OpenGL::absoluteHeight = height;
      OpenGL::outputX = 0;
      OpenGL::outputY = 0;
      OpenGL::outputWidth = windowWidth;
      OpenGL::outputHeight = windowHeight;
      OpenGL::output();

      [[view openGLContext] flushBuffer];
      if(self.flush) glFinish();
      [view unlockFocus];
    }
    releaseContext();*/
  }

private:
  auto acquireContext() -> void {
    
  }

  auto releaseContext() -> void {
    
  }

  auto initialize() -> bool {
    terminate();
    if(!self.fullScreen && !self.context) return false;

    if(self.fullScreen) {
      window = [[RubyWindowMetal alloc] initWith:this];
      [window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
      [window toggleFullScreen:nil];
    }

    auto context = self.fullScreen ? [window contentView] : (__bridge NSView*)(void *)self.context;
    auto size = [context frame].size;

    view = [[RubyVideoMetal alloc] initWith:this pixelFormat:format];
    [view setFrame:NSMakeRect(0, 0, size.width, size.height)];
    [view setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [view setWantsBestResolutionOpenGLSurface:YES];
    [context addSubview:view];
    [[view window] makeFirstResponder:view];
    [view lockFocus];

    Metal::initialize(self.shader);

    s32 blocking = self.blocking;

    [view unlockFocus];

    clear();
    return _ready = true;
  }

  auto terminate() -> void {
    acquireContext();
    _ready = false;
    Metal::terminate();

    if(view) {
      [view removeFromSuperview];
      view = nil;
    }

    if(window) {
    //[NSApp setPresentationOptions:NSApplicationPresentationDefault];
      [window toggleFullScreen:nil];
      [window setCollectionBehavior:NSWindowCollectionBehaviorDefault];
      [window close];
      window = nil;
    }
  }

  RubyVideoMetal* view = nullptr;
  RubyWindowMetal* window = nullptr;

  bool _ready = false;
  std::recursive_mutex mutex;
};

@implementation RubyVideoMetal : MTKView

-(id) initWith:(VideoMetla*)videoPointer pixelFormat:(MTLPixelFormat*)pixelFormat {
  if(self = [super initWithFrame:NSMakeRect(0, 0, 0, 0) pixelFormat:pixelFormat]) {
    video = videoPointer;
  }
  return self;
}

-(void) reshape {
  [super reshape];
  video->output(0, 0);
}

-(BOOL) acceptsFirstResponder {
  return YES;
}

-(void) keyDown:(NSEvent*)event {
}

-(void) keyUp:(NSEvent*)event {
}

@end

@implementation RubyWindowMetal : NSWindow

-(id) initWith:(VideoMetal*)videoPointer {
  auto primaryRect = [[[NSScreen screens] objectAtIndex:0] frame];
  if(self = [super initWithContentRect:primaryRect styleMask:0 backing:NSBackingStoreBuffered defer:YES]) {
    video = videoPointer;
    [self setDelegate:self];
    [self setReleasedWhenClosed:NO];
    [self setAcceptsMouseMovedEvents:YES];
    [self setTitle:@""];
    [self makeKeyAndOrderFront:nil];
  }
  return self;
}

-(BOOL) canBecomeKeyWindow {
  return YES;
}

-(BOOL) canBecomeMainWindow {
  return YES;
}

@end
