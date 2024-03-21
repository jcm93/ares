//
//  metal.hpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>

#include "librashader_ld.h"
#include "ShaderTypes.h"

struct Metal;

static const NSUInteger kMaxBuffersInFlight = 3;

struct Metal {
  auto setShader(const string& pathname) -> void;
  auto clear() -> void;
  auto output() -> void;
  auto initialize(const string& shader) -> bool;
  auto terminate() -> void;
  auto draw_test() -> void;
  
  auto getFormat() const -> GLuint;
  auto getType() const -> GLuint;
  
  auto size(u32 width, u32 height) -> void;
  auto release() -> void;
  auto render(u32 sourceWidth, u32 sourceHeight, u32 targetX, u32 targetY, u32 targetWidth, u32 targetHeight) -> void;
  
  u32 *buffer = nullptr;

  u32 frameCount = 0;
  u32 cpuFrameCount = 0;
  u32 sourceWidth = 0;
  u32 sourceHeight = 0;
  u32 bytesPerRow = 0;
  
  u32 outputWidth = 0;
  u32 outputHeight = 0;
  double _outputX = 0;
  double _outputY = 0;
  
  CGFloat _viewWidth = 0;
  CGFloat _viewHeight = 0;
  
  NSDate *then;
  
  id<MTLDevice> _device;
  id<MTLCommandQueue> _commandQueue;
  id<MTLLibrary> _library;
  dispatch_semaphore_t _semaphore;
  
  vector_uint2 _viewportSize;
  MTKView *viewTest;
  
  id<MTLBuffer> _pixelBuffers[kMaxBuffersInFlight];
  id<MTLBuffer> _vertexBuffer;
  id<MTLDepthStencilState> _depthState;
  id<MTLTexture> _sourceTexture;
  id<MTLTexture> _colorMap;
  MTLVertexDescriptor *_mtlVertexDescriptor;
  
  MTLRenderPassDescriptor *_renderToTextureRenderPassDescriptor;
  id<MTLTexture> _renderTargetTexture;
  id<MTLRenderPipelineState> _renderToTextureRenderPipeline;
  
  id<MTLRenderPipelineState> _drawableRenderPipeline;
  
  libra_instance_t _libra;
  libra_shader_preset_t _preset;
  libra_mtl_filter_chain_t _filterChain;
  libra_viewport_t _libraViewport;
  bool initialized = false;
};
