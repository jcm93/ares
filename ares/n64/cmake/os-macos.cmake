target_sources(ares PRIVATE cmake/os-macos.cmake)

# find_package(MoltenVK)
#
# if(MoltenVK_FOUND)
#   target_link_libraries(ares PRIVATE "$<LINK_LIBRARY:WEAK_LIBRARY,MoltenVK::MoltenVK>")
# endif()
#
# if(MoltenVK_FOUND)
#   set(VULKAN_FOUND true)
# endif()

find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)
  target_link_libraries(ares PRIVATE "$<LINK_LIBRARY:WEAK_LIBRARY,Vulkan::Vulkan>")
  set(VULKAN_FOUND true)
  # find_package(MoltenVK REQUIRED)
  find_package(KosmicKrisp REQUIRED)
  # target_link_libraries(ares PRIVATE "$<LINK_LIBRARY:WEAK_LIBRARY,MoltenVK::MoltenVK>")
  target_link_libraries(ares PRIVATE "$<LINK_LIBRARY:WEAK_LIBRARY,KosmicKrisp::KosmicKrisp>")
endif()
