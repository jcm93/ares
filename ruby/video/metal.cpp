//
//  metal.cpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include "metal/metal.hpp"
#include <iostream>

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

/*@interface MetalLayerDelegate: NSObject<CALayerDelegate, NSViewLayerContentScaleDelegate>
@end

@implementation MetalLayerDelegate
- (BOOL)layer:(CALayer *)layer shouldInheritContentsScale:(CGFloat)newScale fromWindow:(NSWindow *)window
{
  return YES;
}

@end*/

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
    auto newSize = CGSize();
    newSize.width = width;
    newSize.height = height;
    view.drawableSize = newSize;
  }

  auto acquire(u32*& data, u32& pitch, u32 width, u32 height) -> bool override {
    if (framebufferWidth != width || framebufferHeight != height) {
      
      framebufferWidth = width, framebufferHeight = height;
      
      if (buffer) {
        delete[] buffer;
        buffer = nullptr;
      }
      
      buffer = new u32[width * height]();
      for (int i=0; i<kMaxBuffersInFlight;i++) {
        _pixelBuffers[i] = [_device newBufferWithBytes:buffer
                                                length:framebufferWidth*framebufferHeight*4
                                               options:MTLResourceStorageModeManaged];
      }
    }
    pitch = framebufferWidth * sizeof(u32);
    return data = buffer;
  }

  auto release() -> void override {
    
  }
  auto draw_test() -> void {
    
  }

  auto output(u32 width, u32 height) -> void override {
    
    @autoreleasepool {
      
      dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
      
      float widthfloat = (float)width;
      float heightfloat = (float)height;
      
      AAPLVertex vertices[] =
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
        
        id<MTLBuffer> vertexBuffer = [_device newBufferWithBytes:vertices length:sizeof(vertices) options:MTLResourceStorageModeShared];
        
        MTLTextureDescriptor *texDescriptor = [MTLTextureDescriptor new];
        texDescriptor.textureType = MTLTextureType2D;
        texDescriptor.width = width;
        texDescriptor.height = height;
        texDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
        texDescriptor.usage = MTLTextureUsageRenderTarget |
                              MTLTextureUsageShaderRead;
        
        _renderTargetTexture = [_device newTextureWithDescriptor:texDescriptor];
        
        _renderToTextureRenderPassDescriptor.colorAttachments[0].texture = _renderTargetTexture;
        
        if (_renderToTextureRenderPassDescriptor != nil) {
          
          id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:_renderToTextureRenderPassDescriptor];
          
          MTLTextureDescriptor *textureDescriptor = [MTLTextureDescriptor new];
          textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
          textureDescriptor.width = framebufferWidth;
          textureDescriptor.height = framebufferHeight;
          textureDescriptor.usage = MTLTextureUsageRenderTarget|MTLTextureUsageShaderRead;
          
          _renderToTextureRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
          
          auto bytesPerRow = framebufferWidth * 4;
          if (bytesPerRow < 16) bytesPerRow = 16;
          
          auto bufferIndex = frameCount % kMaxBuffersInFlight;
          
          //buffer index does not actually change; placeholder from triple buffer
          id<MTLTexture> metalTexture = [_pixelBuffers[bufferIndex] newTextureWithDescriptor:textureDescriptor
                                                                                      offset:0
                                                                                 bytesPerRow:bytesPerRow];
          
          //just copy into this texture for now
          [metalTexture replaceRegion:MTLRegionMake2D(0, 0, framebufferWidth, framebufferHeight) mipmapLevel:0 withBytes:buffer bytesPerRow:bytesPerRow];
          
          [renderEncoder setRenderPipelineState:_renderToTextureRenderPipeline];
          
          _viewportSize.x = width;
          _viewportSize.y = height;
          
          [renderEncoder setViewport:(MTLViewport){0, 0, (double)width, (double)height, -1.0, 1.0}];
          
          [renderEncoder setVertexBuffer:vertexBuffer
                                  offset:0
                                 atIndex:0];
          
          [renderEncoder setVertexBytes:&_viewportSize
                                 length:sizeof(_viewportSize)
                                atIndex:AAPLVertexInputIndexViewportSize];
          
          [renderEncoder setFragmentTexture:metalTexture atIndex:0];
          
          [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];
          
          [renderEncoder endEncoding];
          
          libra_viewport_t viewport;
          viewport.width = (uint32_t) width;
          viewport.height = (uint32_t) height;
          viewport.x = 0;
          viewport.y = 0;
          
          //std::cout << "w" << width << " " << "w" << height << "\n";
          //std::cout << renderTexture.width << " " << renderTexture.height << "\n";
          
          _libra.mtl_filter_chain_frame(&_filterChain, commandBuffer, frameCount++, metalTexture, viewport, _renderTargetTexture, nil, nil);
          
          MTLRenderPassDescriptor *drawableRenderPassDescriptor = view.currentRenderPassDescriptor;
          
          drawableRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
          
          if (drawableRenderPassDescriptor != nil) {
            
            id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:drawableRenderPassDescriptor];
            
            [renderEncoder setRenderPipelineState:_drawableRenderPipeline];
            
            auto outputX = ((double)(view.frame.size.width * 2 - width) / 2);
            auto outputY = ((double)(view.frame.size.height * 2 - height) / 2);
            
            _viewportSize.x = width;
            _viewportSize.y = height;
            
            [renderEncoder setViewport:(MTLViewport){(double)outputX, (double)outputY, (double)width, (double)height, -1.0, 1.0}];
            
            [renderEncoder setVertexBuffer:vertexBuffer
                                    offset:0
                                   atIndex:0];
            
            [renderEncoder setVertexBytes:&_viewportSize
                                   length:sizeof(_viewportSize)
                                  atIndex:AAPLVertexInputIndexViewportSize];
            
            [renderEncoder setFragmentTexture:_renderTargetTexture atIndex:0];
            
            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];
            
            [renderEncoder endEncoding];
            
            id<CAMetalDrawable> drawable = view.currentDrawable;
            
            if (drawable != nil) {
              
              [commandBuffer presentDrawable:view.currentDrawable];
              
              [view draw];
              
            }
            
          }
          
          [commandBuffer commit];
          
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
    
    MTLTextureDescriptor *texDescriptor = [MTLTextureDescriptor new];
    texDescriptor.textureType = MTLTextureType2D;
    texDescriptor.width = 512;
    texDescriptor.height = 512;
    texDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
    texDescriptor.usage = MTLTextureUsageRenderTarget |
                          MTLTextureUsageShaderRead;

    _renderTargetTexture = [_device newTextureWithDescriptor:texDescriptor];

    // Set up a render pass descriptor for the render pass to render into
    // _renderTargetTexture.

    _renderToTextureRenderPassDescriptor = [MTLRenderPassDescriptor new];

    _renderToTextureRenderPassDescriptor.colorAttachments[0].texture = _renderTargetTexture;

    _renderToTextureRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    _renderToTextureRenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 1, 1, 1);

    _renderToTextureRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    NSURL *shaderLibURL = [NSURL fileURLWithPath:@"ares.app/Contents/Resources/Shaders/shaders.metallib"];
    _library = [_device newLibraryWithURL: shaderLibURL error:&error];
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [MTLRenderPipelineDescriptor new];
    
    // Set up pipeline for rendering to the offscreen texture. Reuse the
    // descriptor and change properties that differ.
    pipelineStateDescriptor.label = @"Offscreen Render Pipeline";
    pipelineStateDescriptor.sampleCount = 1;
    pipelineStateDescriptor.vertexFunction = [_library newFunctionWithName:@"vertexShader"];
    pipelineStateDescriptor.fragmentFunction = [_library newFunctionWithName:@"samplingShader"];
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = _renderTargetTexture.pixelFormat;
    _renderToTextureRenderPipeline = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    
    if (_renderToTextureRenderPipeline == nil) {
      NSLog(@"%@",error);
    }
    
    pipelineStateDescriptor.label = @"Drawable Render Pipeline";
    pipelineStateDescriptor.sampleCount = 1;
    pipelineStateDescriptor.vertexFunction = [_library newFunctionWithName:@"vertexShader"];
    pipelineStateDescriptor.fragmentFunction = [_library newFunctionWithName:@"samplingShader"];
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    //pipelineStateDescriptor.vertexBuffers[AAPLVertexInputIndexVertices].mutability = MTLMutabilityImmutable;
    _drawableRenderPipeline = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    
    if (_drawableRenderPipeline == nil) {
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
    context.autoresizesSubviews = true;
    view.colorspace = CGColorSpaceCreateWithName(kCGColorSpaceDisplayP3);
    view.autoresizingMask = NSViewWidthSizable|NSViewHeightSizable;
    
    /*pipelineDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat;
    pipelineDescriptor.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
    pipelineDescriptor.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;*/

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
  self.enableSetNeedsDisplay = NO;
  self.autoResizeDrawable = YES;
  //[self setAutoresizesSubviews:YES];
  self.paused = YES;
  //[self setPreferredFramesPerSecond:60];
  //[self setDelegate:self];
  return self;
}

-(void) drawInMTKView:(MTKView *)view {
  video->draw_test();
  //[view setNeedsDisplay:YES];
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
