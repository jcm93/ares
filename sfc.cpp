#include <ares/ares.hpp>

#include <component/processor/arm7tdmi/arm7tdmi.hpp>
#include <component/processor/gsu/gsu.hpp>
#include <component/processor/hg51b/hg51b.hpp>
#include <component/processor/spc700/spc700.hpp>
#include <component/processor/upd96050/upd96050.hpp>
#include <component/processor/wdc65816/wdc65816.hpp>

#if defined(CORE_GB)
  #include <gb/gb.hpp>
#endif


#include <sfc/system/system.cpp>
#include <sfc/controller/controller.cpp>
#include <sfc/cartridge/cartridge.cpp>
#include <sfc/memory/memory.cpp>
#include <sfc/cpu/cpu.cpp>
#include <sfc/smp/smp.cpp>
#include <sfc/dsp/dsp.cpp>
#include <sfc/ppu/ppu.cpp>
#include <sfc/ppu-performance/ppu>.cpp
#include <sfc/coprocessor/coprocessor.cpp>
#include <sfc/expansion/expansion.cpp>
#include <sfc/slot/slot.cpp>
