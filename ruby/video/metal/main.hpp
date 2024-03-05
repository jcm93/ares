#if defined(PLATFORM_MACOS)
#import <mach-o/dyld.h>
#endif

auto Metal::setShader(const string& pathname) -> void {

}

auto Metal::clear() -> void {

}

auto Metal::lock(u32*& data, u32& pitch) -> bool {
  return true;
}

auto Metal::output() -> void {

}

auto Metal::initialize(const string& shader) -> bool {

  _libra = librashader_load_instance();
  if(!_libra.instance_loaded) {
    print("Metal: Failed to load librashader: shaders will be disabled\n");
  }
  
  return initialized = true;
}

auto Metal::terminate() -> void {
  
}

