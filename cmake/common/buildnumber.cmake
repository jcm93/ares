include_guard(GLOBAL)

# Define build number cache file
set(_BUILD_NUMBER_CACHE
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/.CMakeBuildNumber"
    CACHE INTERNAL "ares build number cache file")

# Read build number from cache file or manual override
if(NOT DEFINED ARES_BUILD_NUMBER)
  if(EXISTS "${_BUILD_NUMBER_CACHE}")
    file(READ "${_BUILD_NUMBER_CACHE}" ARES_BUILD_NUMBER)
    math(EXPR ARES_BUILD_NUMBER "${ARES_BUILD_NUMBER}+1")
  else()
    if("$ENV{CI}" AND "$ENV{GITHUB_RUN_ID}")
      set(ARES_BUILD_NUMBER "$ENV{GITHUB_RUN_ID}")
    else()
      set(ARES_BUILD_NUMBER "1")
    endif()
  endif()
  file(WRITE "${_BUILD_NUMBER_CACHE}" "${ARES_BUILD_NUMBER}")
endif()
