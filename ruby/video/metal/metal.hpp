//
//  metal.hpp
//  ares
//
//  Created by jcm on 3/4/24.
//

#include <Foundation/Foundation.h>
#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include <MetalKit/MetalKit.h>
#include <MetalKit/MTKView.h>
#include <Metal/MTLDevice.h>

struct Metal;

struct Metal {
  auto setShader(const string& pathname) -> void;
  auto clear() -> void;
  auto lock(u32*& data, u32& pitch) -> bool;
  auto output() -> void;
  auto initialize(const string& shader) -> bool;
  auto terminate() -> void;
};

#include "main.hpp"
