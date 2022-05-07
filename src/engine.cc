#include <iostream>
#include <dlfcn.h>

#include "VulkanFunctions.h"
#include "my_asserts.hh"


int main()
{
  void* vulkan_library = dlopen("libvulkan.so.1", RTLD_NOW);

  if (!vulkan_library)
    std::cout << "Could not connect with Vulkan library." << std::endl;

  #include "ListOfVulkanFunctions.inl"
  PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
  PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
  PFN_vkCreateInstance vkCreateInstance;

  vkEnumerateInstanceExtensionProperties =  (PFN_vkEnumerateInstanceExtensionProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");
  vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties");
  vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInstance");

  CHK_ELSE_RET(vkEnumerateDeviceExtensionProperties);
  CHK_ELSE_RET(vkEnumerateInstanceExtensionProperties);
  CHK_ELSE_RET(vkCreateInstance);

  std::cout << "Program ended successfully !" << std::endl;

  return 0;
}