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

#include "librashader.h"
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
  
  id<MTLDevice> _device;
  id<MTLCommandQueue> _commandQueue;
  
  id<MTLBuffer> _dynamicUniformBuffer;
  id<MTLRenderPipelineState> _pipelineState;
  id<MTLDepthStencilState> _depthState;
  id<MTLTexture> _colorMap;
  MTLVertexDescriptor *_mtlVertexDescriptor;
  
  libra_instance_t _libra;
  libra_shader_preset_t _preset;
  libra_mtl_filter_chain_t _filterChain;
  bool initialized = false;
};

#include "main.hpp"
