#!/usr/bin/env sh

# temp: add dummy tag since downstream
git tag -a 140.0.0 -m "stupid"

# configure
cmake --preset macos-ci ${@}

# change into the build directory
pushd build_macos

# build; pipe output to render warnings neatly
xcodebuild -configuration RelWithDebInfo \
            DEBUG_INFORMATION_FORMAT="dwarf-with-dsym" \
            2>&1 | xcbeautify --renderer github-actions

popd

# package debug symbols

# move dependency dSYMs to build output directory
ditto .deps/ares-deps-macos-universal/lib/*.dSYM build_macos/desktop-ui/RelWithDebInfo

mkdir build_macos/desktop-ui/RelWithDebInfo/dSYMs

# ares.app.dSYM already exists alongside ares.app; package it with the rest
mv build_macos/desktop-ui/RelWithDebInfo/*.dSYM build_macos/desktop-ui/RelWithDebInfo/dSYMs/


