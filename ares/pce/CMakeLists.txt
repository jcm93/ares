add_core_target(pce)

set(
  pce_PRIMARY_SOURCES
  cpu/cpu.cpp
  psg/psg.cpp
  pcd/pcd.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  vdp/vdp.cpp
  vdp-performance/vdp-performance.cpp
)
target_sources(pce PRIVATE ${pce_PRIMARY_SOURCES})

ares_add_components(CORE pce COMPONENT processor/huc6280 audio/msm5205)

target_sources(
  pce
  PRIVATE #
    pce.hpp
    CMakeLists.txt
)

target_sources(
  pce
  PRIVATE #
    cartridge/cartridge.hpp
    cartridge/serialization.cpp
    cartridge/slot.cpp
    cartridge/slot.hpp
    cartridge/board/arcade-card-duo.cpp
    cartridge/board/arcade-card-pro.cpp
    cartridge/board/banked.cpp
    cartridge/board/board.cpp
    cartridge/board/board.hpp
    cartridge/board/debugger.cpp
    cartridge/board/games-express.cpp
    cartridge/board/linear.cpp
    cartridge/board/ram.cpp
    cartridge/board/split.cpp
    cartridge/board/super-system-card.cpp
    cartridge/board/system-card.cpp
)

target_sources(
  pce
  PRIVATE #
    controller/controller.hpp
    controller/port.cpp
    controller/port.hpp
    controller/avenuepad/avenuepad.cpp
    controller/avenuepad/avenuepad.hpp
    controller/gamepad/gamepad.cpp
    controller/gamepad/gamepad.hpp
    controller/multitap/multitap.cpp
    controller/multitap/multitap.hpp
)

target_sources(
  pce
  PRIVATE #
    cpu/cpu.hpp
    cpu/debugger.cpp
    cpu/io.cpp
    cpu/irq.cpp
    cpu/serialization.cpp
)

target_sources(
  pce
  PRIVATE #
    pcd/adpcm.cpp
    pcd/cdda.cpp
    pcd/debugger.cpp
    pcd/drive.cpp
    pcd/fader.cpp
    pcd/io.cpp
    pcd/pcd.hpp
    pcd/scsi.cpp
    pcd/serialization.cpp
)

target_sources(
  pce
  PRIVATE #
    psg/channel.cpp
    psg/io.cpp
    psg/psg.hpp
    psg/serialization.cpp
)

target_sources(
  pce
  PRIVATE #
    system/serialization.cpp
    system/system.hpp
)

target_sources(
  pce
  PRIVATE #
    vdp/background.cpp
    vdp/color.cpp
    vdp/debugger.cpp
    vdp/dma.cpp
    vdp/irq.cpp
    vdp/serialization.cpp
    vdp/sprite.cpp
    vdp/vce.cpp
    vdp/vce.hpp
    vdp/vdc.cpp
    vdp/vdc.hpp
    vdp/vdp.hpp
    vdp/vpc.cpp
    vdp/vpc.hpp
)

target_sources(
  pce
  PRIVATE #
    vdp-performance/background.cpp
    vdp-performance/color.cpp
    vdp-performance/debugger.cpp
    vdp-performance/dma.cpp
    vdp-performance/irq.cpp
    vdp-performance/serialization.cpp
    vdp-performance/sprite.cpp
    vdp-performance/vce.cpp
    vdp-performance/vce.hpp
    vdp-performance/vdc.cpp
    vdp-performance/vdc.hpp
    vdp-performance/vdp.hpp
    vdp-performance/vpc.cpp
    vdp-performance/vpc.hpp
)

organize_core_sources(CORE pce)
if(ARES_UNITY_CORES)
  set_source_files_properties(pce vdp/vdp.cpp vdp-performance/vdp-performance.cpp PROPERTIES HEADER_FILE_ONLY FALSE)
endif()
