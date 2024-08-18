ares_components(
  z80
  tms9918
  sn76489
)

target_sources(ares PRIVATE
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  system/system.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
)

ares_add_header_sources(cv
      # cmake-format: sortable
      cv.hpp CMakeLists.txt)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      cartridge/cartridge.hpp
      cartridge/serialization.cpp
      cartridge/slot.cpp
      cartridge/slot.hpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      cartridge/board/board.cpp
      cartridge/board/board.hpp
      cartridge/board/coleco.cpp
      cartridge/board/megacart.cpp
      cartridge/board/xin1.cpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      controller/controller.hpp
      controller/port.cpp
      controller/port.hpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      controller/gamepad/gamepad.cpp
      controller/gamepad/gamepad.hpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      cpu/cpu.hpp
      cpu/debugger.cpp
      cpu/memory.cpp
      cpu/serialization.cpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      psg/psg.hpp
      psg/serialization.cpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      system/controls.cpp
      system/serialization.cpp
      system/system.hpp)
      
ares_add_header_sources(cv
      # cmake-format: sortable
      vdp/color.cpp
      vdp/serialization.cpp
      vdp/vdp.hpp)
