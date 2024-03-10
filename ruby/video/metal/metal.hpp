//
//  metal.hpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include <Foundation/Foundation.h>
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>
#include <Metal/MTLDevice.h>
#include <ModelIO/ModelIO.h>
#include <CoreImage/CoreImage.h>

#include "librashader_ld.h"
#include "ShaderTypes.h"

struct Metal;

struct Metal {
  auto setShader(const string& pathname) -> void;
  auto clear() -> void;
  auto lock(u32*& data, u32& pitch) -> bool;
  auto output() -> void;
  auto initialize(const string& shader) -> bool;
  auto terminate() -> void;
  
  auto getFormat() const -> GLuint;
  auto getType() const -> GLuint;
  
  auto size(u32 width, u32 height) -> void;
  auto release() -> void;
  auto render(u32 sourceWidth, u32 sourceHeight, u32 targetX, u32 targetY, u32 targetWidth, u32 targetHeight) -> void;
  
  u32* buffer = nullptr;

  u32 frameCount = 0;
  u32 framebufferWidth = 0;
  u32 framebufferHeight = 0;
  
  id<MTLDevice> _device;
  id<MTLCommandQueue> _commandQueue;
  id<MTLLibrary> _library;
  
  vector_uint2 _viewportSize;
  
  id<MTLBuffer> _dynamicUniformBuffer;
  id<MTLRenderPipelineState> _pipelineState;
  id<MTLDepthStencilState> _depthState;
  id<MTLTexture> _colorMap;
  id<MTLBuffer> _mtlBuffer;
  MTLVertexDescriptor *_mtlVertexDescriptor;
  
  libra_instance_t _libra;
  libra_shader_preset_t _preset;
  libra_mtl_filter_chain_t _filterChain;
  bool initialized = false;
};

#include "main.hpp"
