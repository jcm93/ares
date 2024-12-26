# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR ARM64)

set(ENV{PATH} "/opt/aarch64-w64-mingw32/bin:$ENV{PATH}")

# Specify the cross-compilation toolchain
set(CMAKE_C_COMPILER aarch64-w64-mingw32-clang)
set(CMAKE_CXX_COMPILER aarch64-w64-mingw32-clang++)

set(CMAKE_C_FLAGS --target=aarch64-w64-windows-gnu) # --sysroot=/clangarm64/ -resource-dir=/clangarm64/lib/clang/18)
set(CMAKE_CXX_FLAGS --target=aarch64-w64-windows-gnu) # --sysroot=/clangarm64/ -resource-dir=/clangarm64/lib/clang/18)

set(CMAKE_FIND_ROOT_PATH /clangarm64)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
