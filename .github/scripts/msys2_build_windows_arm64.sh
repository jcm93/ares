#!/usr/bin/env sh

# temp: add dummy tag since downstream
git tag v140


echo "arguments are ${@}"
# configure
mkdir build_native

# change into the build directory
cd build_native

cmake .. -G Ninja -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO

# build
cmake --build . --target sourcery

ls

cd ..

mkdir build

cd build

cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/windows/aarch64-cross-toolchain.cmake -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO

cmake --build .

mkdir dsyms

mkdir desktop-ui/RelWithDebInfo
mv desktop-ui/* desktop-ui/RelWithDebInfo

mv desktop-ui/RelWithDebInfo/*.pdb dsyms/

# build


# package debug symbols
