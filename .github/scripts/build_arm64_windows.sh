#!/usr/bin/env sh

# temp: add dummy tag since downstream
git tag v140


echo "arguments are ${@}"
# configure
mkdir build_native


cd build_native

cmake .. -G "Visual Studio 17 2022" -A x64 -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO

cmake --build . --target sourcery --config RelWithDebInfo

ls

cd ..

mkdir build

cd build

cmake .. -G "Visual Studio 17 2022" -A arm64 -DARES_BUILD_LOCAL=NO -DCMAKE_BUILD_TYPE=RelWithDebInfo -DARES_PRECOMPILE_HEADERS=NO -DENABLE_CCACHE=NO -DARES_BUILD_LOCAL=NO -DARES_CROSSCOMPILING=YES

# build
cmake --build . --config RelWithDebInfo

echo "contents of build directory"
ls
echo "contents of build/desktop-ui"
cd desktop-ui
ls
cd ..


mv desktop-ui/Shaders desktop-ui/RelWithDebInfo
mv desktop-ui/Database desktop-ui/RelWithDebInfo

mkdir dsyms

mv desktop-ui/RelWithDebInfo/*.pdb dsyms/

# package debug symbols
