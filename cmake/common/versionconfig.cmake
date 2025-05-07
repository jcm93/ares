include_guard(GLOBAL)

function(get_ares_version_info)
  # Get the canonical version
  if(DEFINED ARES_VERSION_OVERRIDE)
    set(ARES_VERSION ARES_VERSION_OVERRIDE)
    set(ARES_CANONICAL_VERSION_CANDIDATE ${ARES_VERSION_OVERRIDE})
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    execute_process(
      COMMAND git describe --always --tags --exclude=nightly
      OUTPUT_VARIABLE ARES_CANONICAL_VERSION_CANDIDATE
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      RESULT_VARIABLE ares_version_result
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "describe output is ${ARES_CANONICAL_VERSION_CANDIDATE}")
  else()
    file(READ cmake/common/.archive-version ares_tarball_version_json)
    string(JSON ${ares_tarball_version_json} GET ares_tarball_version_tag tag)
    string(STRIP "${ares_tarball_version_tag}" ares_tarball_version_tag)
    set(ARES_CANONICAL_VERSION_CANDIDATE "${ares_tarball_version_tag}")
    set(ARES_DISPLAY_VERSION_CANDIDATE "${ares_tarball_version_tag}")
  endif()
  
  string(REGEX REPLACE "^v([0-9]+(\\.[0-9]+)*)-.*" "\\1" ares_version_stripped "${ARES_CANONICAL_VERSION_CANDIDATE}")
  string(REPLACE "." ";" ares_version_parts "${ares_version_stripped}")
  list(LENGTH ares_version_parts ares_version_parts_length)
  list(GET ares_version_parts 0 major)
  if(ares_version_parts_length GREATER 1)
    list(GET ares_version_parts 1 minor)
  else()
    set(minor 0)
  endif()
  if(ares_version_parts_length GREATER 2)
    list(GET ares_version_parts 2 patch)
  else()
    set(patch 0)
  endif()
  set(ARES_VERSION_CANONICAL "${major}.${minor}.${patch}")
  message(DEBUG "Canonical version set to ${ARES_VERSION_CANONICAL}")
  
  if(NOT ARES_VERSION_CANONICAL MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(STATUS "No recent tags found -- using dummy canonical version")
    set(ARES_VERSION_CANONICAL 0.0.0)
  endif()
  
  if(ARES_VERSION_OVERRIDE)
    return(PROPAGATE ARES_VERSION ARES_VERSION_CANONICAL)
  endif()
  
  # Get the display version
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    execute_process(
      COMMAND git describe --tags --exact-match
      OUTPUT_VARIABLE ARES_DISPLAY_VERSION_CANDIDATE
      ERROR_VARIABLE git_describe_err
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    if(NOT git_describe_err)
      set(exact_match YES)
    else()
      set(exact_match NO)
    endif()
  else()
    if(ARES_DISPLAY_VERSION_CANDIDATE MATCHES "^v([0-9]+(\\.[0-9]+)*)$")
      set(exact_match YES)
    else()
      set(exact_match NO)
    endif()
  endif()
  if(NOT exact_match)
    # Not an exact match; use display branch - commit
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
      execute_process(
        COMMAND git symbolic-ref --short -q HEAD
        OUTPUT_VARIABLE ARES_BRANCH_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      )
      execute_process(
        COMMAND git rev-parse --short HEAD
        OUTPUT_VARIABLE ARES_GIT_COMMIT_SHORTHASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      )
      execute_process(
        COMMAND git status --porcelain
        OUTPUT_VARIABLE ARES_GIT_DIRTY
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      )
    else()
      string(JSON ${ares_tarball_version_json} GET ARES_BRANCH_NAME ref-name)
      string(JSON ${ares_tarball_version_json} GET ARES_GIT_COMMIT_SHORTHASH hash)
    endif()
    set(ARES_VERSION "${ARES_BRANCH_NAME} - ${ARES_GIT_COMMIT_SHORTHASH}")
    if(ARES_GIT_DIRTY)
      set(ARES_VERSION "${ARES_VERSION}-modified")
    endif()
  else()
    set(ARES_VERSION ARES_DISPLAY_VERSION_CANDIDATE)
  endif()
  return(PROPAGATE ARES_VERSION_CANONICAL ARES_VERSION)
endfunction()

get_ares_version_info()
