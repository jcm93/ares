#!/usr/bin/env sh
set -euo pipefail

otherArgs=()

if [ "${MACOS_CERTIFICATE_NAME:-}" != "" ]; then
  echo "Signing using certificate: ${MACOS_CERTIFICATE_NAME}"
  otherArgs+=("-DARES_CODESIGN_IDENTITY=${MACOS_CERTIFICATE_NAME}")
fi

if [ "${MACOS_NOTARIZATION_TEAMID:-}" != "" ]; then
  echo "Signing with team ID: ${MACOS_NOTARIZATION_TEAMID}"
  otherArgs+=("-DARES_CODESIGN_TEAM=${MACOS_NOTARIZATION_TEAMID}")
fi

if ! command -v xcodebuild >/dev/null; then
  cmake --preset macos "${@:-}" "${otherArgs:-}"

  pushd build_macos

  if ! command -v xcbeautify >/dev/null; then
      xcodebuild build -quiet -configuration RelWithDebInfo \
                DEBUG_INFORMATION_FORMAT="dwarf-with-dsym"
  else
      xcodebuild -configuration RelWithDebInfo \
                DEBUG_INFORMATION_FORMAT="dwarf-with-dsym" \
                2>&1 | xcbeautify --renderer terminal
  fi
else
  pushd build_macos
  cmake .. -DARES_BUILD_OPTIONAL_TARGETS=NO -DCMAKE_OSX_DEPLOYMENT_TARGET="10.13" "${otherArgs:-}"
  cmake --build . -j3
fi

open ./desktop-ui/RelWithDebInfo

popd
