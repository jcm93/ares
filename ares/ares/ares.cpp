#include <ares/ares.hpp>
#include <ares/debug/debug.cpp>
#include <nall/gdb/server.cpp>
#include <ares/node/node.cpp>
#include <ares/resource/resource.cpp>

namespace ares {

Platform* platform = nullptr;
bool _runAhead = false;

const u32    SerializerSignature = 0x31545342;  //"BST1" (little-endian)

}
