#if defined(PLATFORM_MACOS)
#import <mach-o/dyld.h>
#endif

#include <iostream>

auto Metal::size(u32 w, u32 h) -> void {
  width = w, height = h;
  buffer = new u32[w * h]();
}

auto Metal::setShader(const string& pathname) -> void {
  if(_libra.mtl_filter_chain_create(&_preset, _commandQueue, nil, &_filterChain) != NULL) {
    print(string{"Metal: Failed to create filter chain for: ", pathname, "\n"});
  };
}

auto Metal::clear() -> void {

}

auto Metal::lock(u32*& data, u32& pitch) -> bool {
  pitch = width * sizeof(u32);
  return data = buffer;
}

auto Metal::output() -> void {
  std::cout << "Metal::output called";
}

auto Metal::render(u32 sourceWidth, u32 sourceHeight, u32 targetX, u32 targetY, u32 targetWidth, u32 targetHeight) -> void {
  std::cout << "Metal::render called";
}

auto Metal::initialize(const string& shader) -> bool {

  _libra = librashader_load_instance();
  if(!_libra.instance_loaded) {
    print("Metal: Failed to load librashader: shaders will be disabled\n");
  }
  
  setShader(shader);
  
  return initialized = true;
}

auto Metal::terminate() -> void {
  
}

