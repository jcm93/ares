find_package(MoltenVK)

if(MoltenVK_FOUND)
  target_link_libraries(n64 PRIVATE "$<LINK_LIBRARY:WEAK_LIBRARY,MoltenVK::MoltenVK>")
endif()

if(MoltenVK_FOUND)
  set(VULKAN_FOUND true)
endif()
