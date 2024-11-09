#!/usr/bin/env sh

# temp: add dummy tag since downstream
git tag v140

which clang++

echo "arguments are ${@}"
# configure
# cmake --preset windows-ci ${@} -DARES_CORES="a26;"

mkdir build
# change into the build directory
cd build

cmake .. -G Ninja -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO --debug-find

# build
cmake --build . --config RelWithDebInfo

mkdir dsyms

mkdir desktop-ui/RelWithDebInfo
mv desktop-ui/* desktop-ui/RelWithDebInfo

mv desktop-ui/RelWithDebInfo/*.pdb dsyms/

cd ..

# package debug symbols
