#include <sljit.h>

#include <nall/pragma.hpp>
#include <nall/platform.hpp>
#include <nall/bump-allocator.hpp>
#include <nall/pragma.hpp>

auto sljit_nall_malloc_exec(sljit_uw size, void* exec_allocator_data) -> void* {
  auto allocator = (nall::bump_allocator*)exec_allocator_data;
  return allocator->tryAcquire(size, false);
}
