# OBS common build dependencies module

# cmake-format: off
# cmake-lint: disable=E1121
# cmake-lint: disable=E1126
# cmake-lint: disable=R0912
# cmake-lint: disable=R0915
# cmake-format: on

include_guard(GLOBAL)

# _check_deps_version: Checks for obs-deps VERSION file in prefix paths
function(_check_deps_version version)
  set(found
      FALSE
      PARENT_SCOPE)

  foreach(path IN LISTS CMAKE_PREFIX_PATH)
    if(EXISTS "${path}/share/obs-deps/VERSION")

      file(READ "${path}/share/obs-deps/VERSION" _check_version)
      string(REPLACE "\n" "" _check_version "${_check_version}")
      string(REPLACE "-" "." _check_version "${_check_version}")
      string(REPLACE "-" "." version "${version}")

      if(_check_version VERSION_EQUAL version)
        set(found
            TRUE
            PARENT_SCOPE)
        break()
      elseif(_check_version VERSION_LESS version)
        message(AUTHOR_WARNING "Older ${label} version detected in ${path}: \n"
                               "Found ${_check_version}, require ${version}")
        list(REMOVE_ITEM CMAKE_PREFIX_PATH "${path}")
        list(APPEND CMAKE_PREFIX_PATH "${path}")
        set(CMAKE_PREFIX_PATH
            ${CMAKE_PREFIX_PATH}
            PARENT_SCOPE)
        continue()
      else()
        message(AUTHOR_WARNING "Newer ${label} version detected in ${path}: \n"
                               "Found ${_check_version}, require ${version}")
        set(found
            TRUE
            PARENT_SCOPE)
        break()
      endif()
    endif()
  endforeach()
endfunction()

# _check_dependencies: Fetch and extract pre-built ares build dependencies
function(_check_dependencies)
  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/buildspec.json" buildspec)

  string(JSON dependency_data GET ${buildspec} dependencies)

  foreach(dependency IN LISTS dependencies_list)

    string(JSON data GET ${dependency_data} ${dependency})
    string(JSON version GET ${data} version)
    string(JSON hash GET ${data} hashes ${platform})
    string(JSON url GET ${data} baseUrl)
    string(JSON label GET ${data} label)
    # cmake-format: off
    string(JSON revision ERROR_VARIABLE error GET ${data} revision ${platform})
    # cmake-format: on

    message(STATUS "Setting up ${label} (${arch})")

    set(file "${${dependency}_filename}")
    set(destination "${${dependency}_destination}")
    string(REPLACE "VERSION" "${version}" file "${file}")
    string(REPLACE "VERSION" "${version}" destination "${destination}")
    string(REPLACE "ARCH" "${arch}" file "${file}")
    string(REPLACE "ARCH" "${arch}" destination "${destination}")
    if(revision)
      string(REPLACE "_REVISION" "_v${revision}" file "${file}")
      string(REPLACE "-REVISION" "-v${revision}" file "${file}")
    else()
      string(REPLACE "_REVISION" "" file "${file}")
      string(REPLACE "-REVISION" "" file "${file}")
    endif()

    if(EXISTS "${dependencies_dir}/.dependency_${dependency}_${arch}.sha256")
      file(READ "${dependencies_dir}/.dependency_${dependency}_${arch}.sha256"
           ARES_DEPENDENCY_${dependency}_${arch}_HASH)
    endif()

    set(skip FALSE)
    if(ARES_DEPENDENCY_${dependency}_${arch}_HASH STREQUAL ${hash})
      _check_deps_version(${version})

      if(found)
        set(skip TRUE)
      endif()
    endif()

    if(skip)
      message(STATUS "Setting up ${label} (${arch}) - skipped")
      continue()
    endif()


    set(url ${url}/${version}/${file})

    if(NOT EXISTS "${dependencies_dir}/${file}")
      message(STATUS "Downloading ${url}")
      file(
        DOWNLOAD "${url}" "${dependencies_dir}/${file}"
        STATUS download_status
        EXPECTED_HASH SHA256=${hash})

      list(GET download_status 0 error_code)
      list(GET download_status 1 error_message)
      if(error_code GREATER 0)
        message(STATUS "Downloading ${url} - Failure")
        message(FATAL_ERROR "Unable to download ${url}, failed with error: ${error_message}")
        file(REMOVE "${dependencies_dir}/${file}")
      else()
        message(STATUS "Downloading ${url} - done")
      endif()
    endif()

    if(NOT ARES_DEPENDENCY_${dependency}_${arch}_HASH STREQUAL ${hash})
      file(REMOVE_RECURSE "${dependencies_dir}/${destination}")
    endif()

    if(NOT EXISTS "${dependencies_dir}/${destination}")
      file(MAKE_DIRECTORY "${dependencies_dir}/${destination}")
      if(dependency STREQUAL ares)
        file(ARCHIVE_EXTRACT INPUT "${dependencies_dir}/${file}" DESTINATION "${dependencies_dir}")
      else()
        file(ARCHIVE_EXTRACT INPUT "${dependencies_dir}/${file}" DESTINATION "${dependencies_dir}/${destination}")
      endif()
    endif()

    file(WRITE "${dependencies_dir}/.dependency_${dependency}_${arch}.sha256" "${hash}")


    list(APPEND CMAKE_PREFIX_PATH "${dependencies_dir}/${destination}")
    message(STATUS "Setting up ${label} (${arch}) - done")
  endforeach()

  list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)

  set(CMAKE_PREFIX_PATH
      ${CMAKE_PREFIX_PATH}
      CACHE PATH "CMake prefix search path" FORCE)
endfunction()
