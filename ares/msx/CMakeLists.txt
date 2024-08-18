ares_components(
  z80
  tms9918
  v9938
  ay38910
  ym2413
)

target_sources(ares PRIVATE
  system/system.cpp
  keyboard/keyboard.cpp
  cartridge/cartridge.cpp
  controller/controller.cpp
  cpu/cpu.cpp
  vdp/vdp.cpp
  psg/psg.cpp
  tape/tape.cpp
  rtc/rtc.cpp
)

ares_add_header_sources(msx
  # cmake-format: sortable
  msx.hpp CMakeLists.txt)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  cartridge/cartridge.hpp
  cartridge/serialization.cpp
  cartridge/slot.cpp
  cartridge/slot.hpp)

ares_add_header_sources(msx
  # cmake-format: sortable
  cartridge/board/asc16.cpp
  cartridge/board/asc8.cpp
  cartridge/board/board.cpp
  cartridge/board/board.hpp
  cartridge/board/cross-blaim.cpp
  cartridge/board/konami-scc.cpp
  cartridge/board/konami.cpp
  cartridge/board/linear.cpp
  cartridge/board/mirrored.cpp
  cartridge/board/super-lode-runner.cpp
  cartridge/board/super-pierrot.cpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  controller/controller.hpp
  controller/mux.cpp
  controller/mux.hpp
  controller/port.cpp
  controller/port.hpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  controller/gamepad/gamepad.cpp
  controller/gamepad/gamepad.hpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  controller/vaus-paddle/vaus-paddle.cpp
  controller/vaus-paddle/vaus-paddle.hpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  cpu/cpu.hpp
  cpu/debugger.cpp
  cpu/memory.cpp
  cpu/serialization.cpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  keyboard/keyboard.hpp
  keyboard/serialization.cpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  psg/psg.hpp
  psg/serialization.cpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  rtc/rtc.hpp
  rtc/serialization.cpp)

ares_add_header_sources(msx
  # cmake-format: sortable
  system/serialization.cpp
  system/system.hpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  tape/deck.cpp
  tape/deck.hpp
  tape/tape.hpp
  tape/tray.cpp
  tape/tray.hpp)
  
ares_add_header_sources(msx
  # cmake-format: sortable
  vdp/color.cpp
  vdp/serialization.cpp
  vdp/vdp.hpp)
