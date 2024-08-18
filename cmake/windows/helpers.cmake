include_guard(GLOBAL)

include(helpers_common)


function(set_target_properties_ares target)
  set(options "")
  set(oneValueArgs "")
  set(multiValueArgs PROPERTIES)
  cmake_parse_arguments(PARSE_ARGV 0 _STPO "${options}" "${oneValueArgs}" "${multiValueArgs}")

  message(DEBUG "Setting additional properties for target ${target}...")

  while(_STPO_PROPERTIES)
    list(POP_FRONT _STPO_PROPERTIES key value)
    set_property(TARGET ${target} PROPERTY ${key} "${value}")
  endwhile()

  get_target_property(target_type ${target} TYPE)

  if(target_type STREQUAL EXECUTABLE)
    get_property(ares_executables GLOBAL PROPERTY _ARES_EXECUTABLES)
    # add_dependencies(${target} ${ares_executables} ${ares_modules})
    _bundle_dependencies(${target})
  elseif(target_type STREQUAL SHARED_LIBRARY)
    set_target_properties(${target} PROPERTIES VERSION ${ARES_VERSION_MAJOR} SOVERSION ${ARES_VERSION_CANONICAL})

    _target_install_ares(
      ${target}
        DESTINATION "${ARES_EXECUTABLE_DESTINATION}"
        LIBRARY_DESTINATION "${ARES_LIBRARY_DESTINATION}"
        HEADER_DESTINATION "${ARES_INCLUDE_DESTINATION}"
    )
  elseif(target_type STREQUAL MODULE_LIBRARY)
    set_target_properties(${target} PROPERTIES VERSION 0 SOVERSION ${ARES_VERSION_CANONICAL})
    set(target_destination "${ARES_DATA_DESTINATION}")

    _target_install_ares(${target} DESTINATION ${target_destination})

    set_property(GLOBAL APPEND PROPERTY ARES_MODULES_ENABLED ${target})
  endif()

  target_link_options(${target} PRIVATE "/PDBALTPATH:$<TARGET_PDB_FILE_NAME:${target}>")
  target_install_resources(${target})

  get_target_property(target_sources ${target} SOURCES)
  set(target_ui_files ${target_sources})
  list(FILTER target_ui_files INCLUDE REGEX ".+\\.(ui|qrc)")
  source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "UI Files" FILES ${target_ui_files})
endfunction()

# _target_install_ares: Helper function to install build artifacts to rundir and install location
function(_target_install_ares target)
  set(options "x86" "x64")
  set(oneValueArgs "DESTINATION" "LIBRARY_DESTINATION" "HEADER_DESTINATION")
  set(multiValueArgs "")
  cmake_parse_arguments(PARSE_ARGV 0 _TIO "${options}" "${oneValueArgs}" "${multiValueArgs}")

  if(_TIO_x86)
    get_target_property(target_type ${target} TYPE)
    if(target_type STREQUAL EXECUTABLE)
      set(suffix exe)
    else()
      set(suffix dll)
    endif()

    cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR BASE_DIRECTORY "${ARES_SOURCE_DIR}" OUTPUT_VARIABLE project_path)

    set(32bit_project_path "${ARES_SOURCE_DIR}/build_x86/${project_path}")
    set(target_file "${32bit_project_path}/$<CONFIG>/${target}32.${suffix}")
    set(target_pdb_file "${32bit_project_path}/$<CONFIG>/${target}32.pdb")
    set(comment "Copy ${target} (x86) to destination")

    install(
      FILES "${32bit_project_path}/$<CONFIG>/${target}32.${suffix}"
      DESTINATION "${_TIO_DESTINATION}"
      COMPONENT Runtime
      OPTIONAL
    )
  elseif(_TIO_x64)
    get_target_property(target_type ${target} TYPE)
    if(target_type STREQUAL EXECUTABLE)
      set(suffix exe)
    else()
      set(suffix dll)
    endif()

    cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR BASE_DIRECTORY "${ARES_SOURCE_DIR}" OUTPUT_VARIABLE project_path)

    set(32bit_project_path "${ARES_SOURCE_DIR}/build_x64/${project_path}")
    set(target_file "${32bit_project_path}/$<CONFIG>/${target}64.${suffix}")
    set(target_pdb_file "${32bit_project_path}/$<CONFIG>/${target}64.pdb")
    set(comment "Copy ${target} (x64) to destination")

    install(
      FILES "${32bit_project_path}/$<CONFIG>/${target}64.${suffix}"
      DESTINATION "${_TIO_DESTINATION}"
      COMPONENT Runtime
      OPTIONAL
    )
  else()
    set(target_file "$<TARGET_FILE:${target}>")
    set(target_pdb_file "$<TARGET_PDB_FILE:${target}>")
    set(comment "Copy ${target} to destination")

    get_target_property(target_type ${target} TYPE)
    if(target_type STREQUAL EXECUTABLE)
      install(TARGETS ${target} RUNTIME DESTINATION "${_TIO_DESTINATION}" COMPONENT Runtime)
    elseif(target_type STREQUAL SHARED_LIBRARY)
      if(NOT _TIO_LIBRARY_DESTINATION)
        set(_TIO_LIBRARY_DESTINATION ${_TIO_DESTINATION})
      endif()
      if(NOT _TIO_HEADER_DESTINATION)
        set(_TIO_HEADER_DESTINATION include)
      endif()
      install(
        TARGETS ${target}
        RUNTIME DESTINATION "${_TIO_DESTINATION}"
        LIBRARY DESTINATION "${_TIO_LIBRARY_DESTINATION}" COMPONENT Runtime EXCLUDE_FROM_ALL
        PUBLIC_HEADER DESTINATION "${_TIO_HEADER_DESTINATION}" COMPONENT Development EXCLUDE_FROM_ALL
      )
    elseif(target_type STREQUAL MODULE_LIBRARY)
      install(
        TARGETS ${target}
        LIBRARY DESTINATION "${_TIO_DESTINATION}" COMPONENT Runtime NAMELINK_COMPONENT Development
      )
    endif()
  endif()

  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E echo "${comment}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_OUTPUT_DIR}/$<CONFIG>/${_TIO_DESTINATION}"
    COMMAND "${CMAKE_COMMAND}" -E copy ${target_file} "${ARES_OUTPUT_DIR}/$<CONFIG>/${_TIO_DESTINATION}"
    COMMAND
      "${CMAKE_COMMAND}" -E $<IF:$<CONFIG:Debug,RelWithDebInfo,Release>,copy,true> ${target_pdb_file}
      "${ARES_OUTPUT_DIR}/$<CONFIG>/${_TIO_DESTINATION}"
    COMMENT ""
    VERBATIM
  )

  install(
    FILES ${target_pdb_file}
    CONFIGURATIONS RelWithDebInfo Debug Release
    DESTINATION "${_TIO_DESTINATION}"
    COMPONENT Runtime
    OPTIONAL
  )
endfunction()

# Helper function to add resources into bundle
function(target_install_resources target)
  message(DEBUG "Installing resources for target ${target}...")
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/data")
    file(GLOB_RECURSE data_files "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
    foreach(data_file IN LISTS data_files)
      cmake_path(
        RELATIVE_PATH
        data_file
        BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/"
        OUTPUT_VARIABLE relative_path
      )
      cmake_path(GET relative_path PARENT_PATH relative_path)
      target_sources(${target} PRIVATE "${data_file}")
      source_group("Resources/${relative_path}" FILES "${data_file}")
    endforeach()

    get_property(ares_module_list GLOBAL PROPERTY ARES_MODULES_ENABLED)
    if(target IN_LIST ares_module_list)
      set(target_destination "${ARES_DATA_DESTINATION}/ares-plugins/${target}")
    elseif(target STREQUAL desktop-ui)
      set(target_destination "${ARES_DATA_DESTINATION}/desktop-ui")
    else()
      set(target_destination "${ARES_DATA_DESTINATION}/${target}")
    endif()

    install(
      DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/"
      DESTINATION "${target_destination}"
      USE_SOURCE_PERMISSIONS
      COMPONENT Runtime
    )

    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E echo "Copy ${target} resources to data directory"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_OUTPUT_DIR}/$<CONFIG>/${target_destination}"
      COMMAND
        "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "${ARES_OUTPUT_DIR}/$<CONFIG>/${target_destination}"
      COMMENT ""
      VERBATIM
    )
  endif()
endfunction()

# Helper function to add a specific resource to a bundle
function(target_add_resource target resource)
  get_property(ares_module_list GLOBAL PROPERTY ARES_MODULES_ENABLED)
  if(ARGN)
    set(target_destination "${ARGN}")
  elseif(${target} IN_LIST ares_module_list)
    set(target_destination "${ARES_DATA_DESTINATION}/ares-plugins/${target}")
  elseif(target STREQUAL desktop-ui)
    set(target_destination "${ARES_DATA_DESTINATION}/desktop-ui")
  else()
    set(target_destination "${ARES_DATA_DESTINATION}/${target}")
  endif()

  message(DEBUG "Add resource '${resource}' to target ${target} at destination '${target_destination}'...")

  install(FILES "${resource}" DESTINATION "${target_destination}" COMPONENT Runtime)

  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E echo "Copy ${target} resource ${resource} to library directory"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_OUTPUT_DIR}/$<CONFIG>/${target_destination}/"
    COMMAND "${CMAKE_COMMAND}" -E copy "${resource}" "${ARES_OUTPUT_DIR}/$<CONFIG>/${target_destination}/"
    COMMENT ""
    VERBATIM
  )

  source_group("Resources" FILES "${resource}")
endfunction()

# _bundle_dependencies: Resolve third party dependencies and add them to Windows binary directory
function(_bundle_dependencies target)
  message(DEBUG "Discover dependencies of target ${target}...")
  set(found_dependencies)
  find_dependencies(TARGET ${target} FOUND_VAR found_dependencies)

  get_property(ares_module_list GLOBAL PROPERTY ARES_MODULES_ENABLED)
  list(LENGTH ares_module_list num_modules)
  if(num_modules GREATER 0)
    add_dependencies(${target} ${ares_module_list})
    foreach(module IN LISTS ares_module_list)
      find_dependencies(TARGET ${module} FOUND_VAR found_dependencies)
    endforeach()
  endif()

  list(REMOVE_DUPLICATES found_dependencies)
  set(library_paths_DEBUG)
  set(library_paths_RELWITHDEBINFO)
  set(library_paths_RELEASE)
  set(library_paths_MINSIZEREL)
  set(plugins_list)

  foreach(library IN LISTS found_dependencies)
    get_target_property(library_type ${library} TYPE)
    get_target_property(is_imported ${library} IMPORTED)

    if(is_imported)
      get_target_property(imported_location ${library} IMPORTED_LOCATION)

      foreach(config IN ITEMS RELEASE RELWITHDEBINFO MINSIZEREL DEBUG)
        get_target_property(imported_location_${config} ${library} IMPORTED_LOCATION_${config})
        if(imported_location_${config})
          _check_library_location(${imported_location_${config}})
        elseif(NOT imported_location_${config} AND imported_location_RELEASE)
          _check_library_location(${imported_location_RELEASE})
        else()
          _check_library_location(${imported_location})
        endif()
      endforeach()
    endif()
  endforeach()

  foreach(config IN ITEMS DEBUG RELWITHDEBINFO RELEASE MINSIZEREL)
    list(REMOVE_DUPLICATES library_paths_${config})
  endforeach()

  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E echo "Copy dependencies to binary directory (${ARES_EXECUTABLE_DESTINATION})..."
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${ARES_OUTPUT_DIR}/$<CONFIG>/${ARES_EXECUTABLE_DESTINATION}"
    COMMAND
      "${CMAKE_COMMAND}" -E "$<IF:$<CONFIG:Debug>,copy_if_different,true>" "$<$<CONFIG:Debug>:${library_paths_DEBUG}>"
      "${ARES_OUTPUT_DIR}/$<CONFIG>/${ARES_EXECUTABLE_DESTINATION}"
    COMMAND
      "${CMAKE_COMMAND}" -E "$<IF:$<CONFIG:RelWithDebInfo>,copy_if_different,true>"
      "$<$<CONFIG:RelWithDebInfo>:${library_paths_RELWITHDEBINFO}>"
      "${ARES_OUTPUT_DIR}/$<CONFIG>/${ARES_EXECUTABLE_DESTINATION}"
    COMMAND
      "${CMAKE_COMMAND}" -E "$<IF:$<CONFIG:Release>,copy_if_different,true>"
      "$<$<CONFIG:Release>:${library_paths_RELEASE}>" "${ARES_OUTPUT_DIR}/$<CONFIG>/${ARES_EXECUTABLE_DESTINATION}"
    COMMAND
      "${CMAKE_COMMAND}" -E "$<IF:$<CONFIG:MinSizeRel>,copy_if_different,true>"
      "$<$<CONFIG:MinSizeRel>:${library_paths_MINSIZEREL}>" "${ARES_OUTPUT_DIR}/$<CONFIG>/${ARES_EXECUTABLE_DESTINATION}"
    COMMENT "."
    VERBATIM
    COMMAND_EXPAND_LISTS
  )

  install(
    FILES ${library_paths_DEBUG}
    CONFIGURATIONS Debug
    DESTINATION "${ARES_EXECUTABLE_DESTINATION}"
    COMPONENT Runtime
  )

  install(
    FILES ${library_paths_RELWITHDEBINFO}
    CONFIGURATIONS RelWithDebInfo
    DESTINATION "${ARES_EXECUTABLE_DESTINATION}"
    COMPONENT Runtime
  )

  install(
    FILES ${library_paths_RELEASE}
    CONFIGURATIONS Release
    DESTINATION "${ARES_EXECUTABLE_DESTINATION}"
    COMPONENT Runtime
  )

  install(
    FILES ${library_paths_MINSIZEREL}
    CONFIGURATIONS MinSizeRel
    DESTINATION "${ARES_EXECUTABLE_DESTINATION}"
    COMPONENT Runtime
  )
endfunction()

# _check_library_location: Check for corresponding DLL given an import library path
macro(_check_library_location location)
  if(library_type STREQUAL "SHARED_LIBRARY")
    set(library_location "${location}")
  else()
    string(STRIP "${location}" location)
    if(location MATCHES ".+lib$")
      cmake_path(GET location FILENAME _dll_name)
      cmake_path(GET location PARENT_PATH _implib_path)
      cmake_path(SET _bin_path NORMALIZE "${_implib_path}/../bin")
      string(REPLACE ".lib" ".dll" _dll_name "${_dll_name}")
      string(REPLACE ".dll" ".pdb" _pdb_name "${_dll_name}")

      find_program(_dll_path NAMES "${_dll_name}" HINTS ${_implib_path} ${_bin_path} NO_CACHE NO_DEFAULT_PATH)

      find_program(_pdb_path NAMES "${_pdb_name}" HINTS ${_implib_path} ${_bin_path} NO_CACHE NO_DEFAULT_PATH)

      if(_dll_path)
        set(library_location "${_dll_path}")
        set(library_pdb_location "${_pdb_path}")
      else()
        unset(library_location)
        unset(library_pdb_location)
      endif()
      unset(_dll_path)
      unset(_pdb_path)
      unset(_bin_path)
      unset(_implib_path)
      unset(_dll_name)
      unset(_pdb_name)
    else()
      unset(library_location)
      unset(library_pdb_location)
    endif()
  endif()

  if(library_location)
    list(APPEND library_paths_${config} ${library_location})
  endif()
  if(library_pdb_location)
    list(APPEND library_paths_${config} ${library_pdb_location})
  endif()
  unset(location)
  unset(library_location)
  unset(library_pdb_location)
endmacro()
