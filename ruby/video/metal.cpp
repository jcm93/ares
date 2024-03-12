//
//  metal.cpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include "metal/metal.hpp"
#include <iostream>

static const NSUInteger kMaxBuffersInFlight = 3;

struct VideoMetal;

@interface RubyVideoMetal : MTKView <MTKViewDelegate> {
@public
  VideoMetal* video;
}
-(id) initWith:(VideoMetal*)video frame:(NSRect)frame device:(id<MTLDevice>)metalDevice;
-(void) reshape;
-(BOOL) acceptsFirstResponder;
-(void) drawInMTKView:(MTKView *)view;
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

  auto setShader(string pathname) -> bool override {
    if (pathname == "Blur") return true;
    
    if(_libra.preset_create(pathname.data(), &_preset) != NULL) {
      print(string{"Metal: Failed to load shader: ", pathname, "\n"});
      return false;
    }
    
    if (_libra.mtl_filter_chain_create(&_preset, _commandQueue, nil, &_filterChain) != NULL) {
      print(string{"Metal: Failed to create filter chain for: ", pathname, "\n"});
      return false;
    };
    return true;
  }

  auto focused() -> bool override {
    return true;
  }

  auto clear() -> void override {
    
  }

  auto size(u32& width, u32& height) -> void override {
    auto area = [view convertRectToBacking:[view bounds]];
    width = area.size.width;
    height = area.size.height;
    _viewportSize.x = width;
    _viewportSize.y = height;
  }

  auto acquire(u32*& data, u32& pitch, u32 width, u32 height) -> bool override {
    if (framebufferWidth != width || framebufferHeight != height) {
      
      framebufferWidth = width, framebufferHeight = height;
      
      if (buffer) {
        delete[] buffer;
        buffer = nullptr;
      }
      
      buffer = new u32[width * height]();
      _mtlBuffer = [_device newBufferWithBytes:buffer
                                        length:framebufferWidth*framebufferHeight*4
                                       options:MTLResourceStorageModeManaged];
    }
    bool result = lock(data, pitch);
    return result;
  }
  
  auto lock(u32*& data, u32& pitch) -> bool {
    pitch = framebufferWidth * sizeof(u32);
    return data = buffer;
  }

  auto release() -> void override {
  }
  
  auto draw_test() -> void override {

  }

  auto output(u32 width, u32 height) -> void override {
    @autoreleasepool {
      
      dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
      
      float widthfloat = (float)width;
      float heightfloat = (float)height;
      
      static const AAPLVertex vertices[] =
      {
        // Pixel positions, Texture coordinates
        { {  widthfloat / 2,  -heightfloat / 2 },  { 1.f, 1.f } },
        { { -widthfloat / 2,  -heightfloat / 2 },  { 0.f, 1.f } },
        { { -widthfloat / 2,   heightfloat / 2 },  { 0.f, 0.f } },
        
        { {  widthfloat / 2,  -heightfloat / 2 },  { 1.f, 1.f } },
        { { -widthfloat / 2,   heightfloat / 2 },  { 0.f, 0.f } },
        { {  widthfloat / 2,   heightfloat / 2 },  { 1.f, 0.f } },
      };
      
      id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
      
      if (commandBuffer != nil) {
        __block dispatch_semaphore_t block_sema = _semaphore;
        
        [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
         dispatch_semaphore_signal(block_sema);
        }];
        
        MTLRenderPassDescriptor *renderPassDescriptor = [view currentRenderPassDescriptor];
        
        id<MTLBuffer> vertexBuffer = [_device newBufferWithBytes:vertices length:sizeof(vertices) options:MTLResourceStorageModeShared];
        
        if (renderPassDescriptor != nil) {
          
          id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
          
          if (renderEncoder!= nil) {
            
            MTLTextureDescriptor *textureDescriptor = [MTLTextureDescriptor new];
            textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
            textureDescriptor.width = framebufferWidth;
            textureDescriptor.height = framebufferHeight;
            textureDescriptor.usage = MTLTextureUsageRenderTarget|MTLTextureUsageShaderRead;
            
            auto bytesPerRow = framebufferWidth * 4;
            if (bytesPerRow < 16) bytesPerRow = 16;
            
            id<MTLTexture> metalTexture = [_mtlBuffer newTextureWithDescriptor:textureDescriptor
                                                                        offset:0
                                                                   bytesPerRow:bytesPerRow];
            
            [metalTexture replaceRegion:MTLRegionMake2D(0, 0, framebufferWidth, framebufferHeight) mipmapLevel:0 withBytes:buffer bytesPerRow:bytesPerRow];
            renderPassDescriptor.colorAttachments[0].texture = metalTexture;
            
            auto length = width * height * 4;
            
            [renderEncoder setRenderPipelineState:_pipelineState];
            
            [renderEncoder setViewport:(MTLViewport){0.0, 0.0, (double)width, (double)height, -1.0, 1.0 }];
            
            [renderEncoder setVertexBuffer:vertexBuffer
                                    offset:0
                                   atIndex:0];
            
            [renderEncoder setVertexBytes:&_viewportSize
                                   length:sizeof(_viewportSize)
                                  atIndex:AAPLVertexInputIndexViewportSize];
            
            [renderEncoder setFragmentTexture:metalTexture atIndex:0];
            
            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];
            
            [renderEncoder endEncoding];
            
            id<MTLTexture> renderTexture = [renderPassDescriptor.colorAttachments[0] texture];
            
            libra_viewport_t viewport;
            viewport.width = (uint32_t) width;
            viewport.height = (uint32_t) height;
            viewport.x = 0;
            viewport.y = 0;
            
            id<CAMetalDrawable> drawable = view.currentDrawable;
            
            _libra.mtl_filter_chain_frame(&_filterChain, commandBuffer, frameCount++, metalTexture, viewport, drawable.texture, nil, nil);
            
            if (drawable != nil) {
              
              [drawable present];
              
              [view draw];
              
            }
            
            [commandBuffer commit];
            
          }
        }
      }
    }
  }

private:
  auto acquireContext() -> void {
    
  }

  auto releaseContext() -> void {
    
  }

  auto initialize() -> bool {
    terminate();
    if (!self.fullScreen && !self.context) return false;

    auto context = self.fullScreen ? [window contentView] : (__bridge NSView*)(void *)self.context;
    auto size = [context frame].size;
    
    NSError *error = nil;
    
    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];
    
    std::cout << size.width << " " << size.height;
    
    _semaphore = dispatch_semaphore_create(kMaxBuffersInFlight);
    
    NSURL *shaderLibURL = [NSURL fileURLWithPath:@"ares.app/Contents/Resources/Shaders/shaders.metallib"];
    _library = [_device newLibraryWithURL: shaderLibURL error:&error];
    
    MTLRenderPipelineDescriptor *pipelineDescriptor = [MTLRenderPipelineDescriptor new];
    pipelineDescriptor.label = @"ares Pipeline";
    pipelineDescriptor.vertexFunction = [_library newFunctionWithName:@"vertexShader"];
    
    pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    pipelineDescriptor.fragmentFunction = [_library newFunctionWithName:@"samplingShader"];
    
    
    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
    
    if (_pipelineState == nil) {
      NSLog(@"%@",error);
    }
    
    //NSDictionary* options = @{kCIContextCacheIntermediates:@NO, kCIContextUseSoftwareRenderer:@NO};
    //_ciContext = [CIContext contextWithMTLCommandQueue:_commandQueue
                                               //options:options];
    
    auto frame = NSMakeRect(0, 0, size.width, size.height);
    view = [[RubyVideoMetal alloc] initWith:this frame:frame device:_device];
    [context addSubview:view];
    [[view window] makeFirstResponder:view];
    [view lockFocus];
    viewTest = view;
    view.colorspace = CGColorSpaceCreateWithName(kCGColorSpaceDisplayP3);
    
    pipelineDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat;
    pipelineDescriptor.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
    pipelineDescriptor.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;

    _commandQueue = [_device newCommandQueue];

    _libra = librashader_load_instance();
    if(!_libra.instance_loaded) {
      print("Metal: Failed to load librashader: shaders will be disabled\n");
    }
    
    setShader(self.shader);

    s32 blocking = self.blocking;

    [view unlockFocus];

    clear();
    initialized = true;
    return _ready = true;
  }

  auto terminate() -> void {
    acquireContext();
    _ready = false;

    if (view) {
      [view removeFromSuperview];
      view = nil;
    }

    if (window) {
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

-(id) initWith:(VideoMetal*)videoPointer frame:(NSRect)frame device:(id<MTLDevice>)metalDevice {
  if(self = [super initWithFrame:frame device:metalDevice]) {
    video = videoPointer;
  }
  self.enableSetNeedsDisplay = YES;
  self.autoResizeDrawable = YES;
  self.paused = YES;
  //[self setDelegate:self];
  return self;
}

-(void) drawInMTKView:(MTKView *)view {
  video->draw_test();
  [view setNeedsDisplay:YES];
}

-(void) reshape {
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
  if (self = [super initWithContentRect:primaryRect styleMask:0 backing:NSBackingStoreBuffered defer:YES]) {
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
