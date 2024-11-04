#!/bin/bash
set -euo pipefail

# Change to parent directory (top-level)
cd "$(dirname "$0")"/.. || exit 1

mkdir build
cd build
cmake .. -G "Xcode" -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
                    -DENABLE_CCACHE=NO \
                    -DARES_BUILD_LOCAL=NO \
                    -DCMAKE_OSX_DEPLOYMENT_TARGET="10.13" \
                    -DARES_CODESIGN_IDENTITY=$penv{CODESIGN_IDENT} \
                    -DARES_CODESIGN_TEAM=$penv{CODESIGN_TEAM}

xcodebuild build 2>&1 | xcbeautify --renderer terminal

echo "Assembling universal binary"
rm -rf desktop-ui/out
cp -a desktop-ui/out-amd64 desktop-ui/out
lipo -create -output desktop-ui/out/ares.app/Contents/MacOS/ares \
    desktop-ui/out-amd64/ares.app/Contents/MacOS/ares \
    desktop-ui/out-arm64/ares.app/Contents/MacOS/ares

if [ "${MACOS_KEYCHAIN_PASSWORD:-}" != "" ]; then
    security unlock-keychain -p "$MACOS_KEYCHAIN_PASSWORD" "$MACOS_KEYCHAIN_NAME"
fi

if [ "${MACOS_CERTIFICATE_NAME:-}" == "" ]; then
    echo "Signing using self-signed"
    ENTITLEMENTS=desktop-ui/resource/ares.selfsigned.entitlements
else
    echo "Signing using certificate: ${MACOS_CERTIFICATE_NAME}"
    ENTITLEMENTS=desktop-ui/resource/ares.entitlements
fi
codesign --force --deep --options runtime --entitlements "${ENTITLEMENTS}" --sign "${MACOS_CERTIFICATE_NAME:--}" desktop-ui/out/ares.app
