include_guard(GLOBAL)

include(helpers_common)


function(ares_configure_executable target)
  get_target_property(target_type ${target} TYPE)

  if(target_type STREQUAL EXECUTABLE)

    _bundle_dependencies(${target})

    install(TARGETS ${target} BUNDLE DESTINATION "." COMPONENT Application)
  endif()
endfunction()

function(_bundle_dependencies target)

endfunction()
