#include <iostream>
#include <dlfcn.h>

#include "VulkanFunctions.h"

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
  vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInsance");

  return 0;
}