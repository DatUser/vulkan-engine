#include <dlfcn.h>
#include <iostream>
#include <vector>

#include "my_asserts.hh"
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

  //
  //  Loading global level-functions
  //

  //Use to check available instance-level extension
  vkEnumerateInstanceExtensionProperties =  (PFN_vkEnumerateInstanceExtensionProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");
  //Use to check available layer
  vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties");
  //Use to create instance
  vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInstance");

  CHK_ELSE_RET(vkEnumerateDeviceExtensionProperties);
  CHK_ELSE_RET(vkEnumerateInstanceExtensionProperties);
  CHK_ELSE_RET(vkCreateInstance);

  //
  //  Checking available instance extensions
  //

  uint32_t nNbExtensions = 0;
  CHK_VK_SUCCESS(vkEnumerateInstanceExtensionProperties(nullptr, &nNbExtensions, nullptr));
  std::cout << nNbExtensions <<  ": Available instance-level extension." << std::endl;

  std::vector<VkExtensionProperties> vAvailableExtensions(nNbExtensions);
  CHK_VK_SUCCESS(vkEnumerateInstanceExtensionProperties(nullptr, &nNbExtensions, vAvailableExtensions.data()));

  //
  //  Create Vulkan instance
  //

  std::vector<char const *> vDesiredExtension;
  VkApplicationInfo vkApplicationInfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = nullptr,
    .pApplicationName = "Vulkan Engine",
    .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
    .pEngineName = "Boo",
    .engineVersion = VK_MAKE_VERSION(1, 0, 0),
    .apiVersion = VK_MAKE_VERSION(1, 0, 0)
  };

  VkInstanceCreateInfo vkInstanceCreateInfo = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .pApplicationInfo = &vkApplicationInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = vDesiredExtension.size(),
    .ppEnabledExtensionNames = vDesiredExtension.size() ? vDesiredExtension.data() : nullptr
  };

  VkInstance vkInstance;
  CHK_VK_SUCCESS(vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vkInstance));

  std::cout << "Program ended successfully !" << std::endl;

  return 0;
}