#!/usr/bin/env sh

# temp: add dummy tag since downstream
git tag v140

which clang++

echo "arguments are ${@}"
# configure
mkdir build

# change into the build directory
cd build

cmake .. -G "Visual Studio 17 2022" -A x64 -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO
# build
cmake --build . --config RelWithDebInfo

mv desktop-ui/Shaders desktop-ui/RelWithDebInfo
mv desktop-ui/Database desktop-ui/RelWithDebInfo

mkdir dsyms

mv desktop-ui/RelWithDebInfo/*.pdb dsyms/

cd ..

# package debug symbols
