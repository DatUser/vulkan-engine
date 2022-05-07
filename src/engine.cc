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


  #define INSTANCE_LEVEL_VULKAN_FUNCTION( name )                          \
    name = (PFN_##name)vkGetInstanceProcAddr( instance, #name );          \
    if( name == nullptr ) {                                               \
      std::cout << "Could not load instance-level Vulkan function named: "\
      #name << std::endl;                                                 \
      return 1;                                                           \
    }

  #define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( name, extension )     \
    for( auto & enabled_extension : enabled_extensions ) {                     \
      if( std::string( enabled_extension ) == std::string( extension ) ) {     \
        name = (PFN_##name)vkGetInstanceProcAddr( instance, #name );           \
        if( name == nullptr ) {                                                \
          std::cout << "Could not load instance-level Vulkan function named: " \
          #name << std::endl;                                                  \
          return false;                                                        \
        }                                                                      \
      }                                                                        \
    }

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

  //
  //Loading instance-level functions
  //


  //
  //  Enumerate availale physical devices
  //

  uint32_t nNbDevices = 0;
  CHK_VK_SUCCESS(vkEnumeratePhysicalDevices(vkInstance, &nNbDevices, nullptr));

  std::vector<VkPhysicalDevice> vAvailableDevices(nNbDevices);
  CHK_VK_SUCCESS(vkEnumeratePhysicalDevices(vkInstance, &nNbDevices, vAvailableDevices.data()));
  std::cout << nNbDevices << ": Available devices." << std::endl;

  if (!nNbDevices)  return 1;

  //
  //  Checking available device extensions
  //

  VkPhysicalDevice vkPhysicalDevice = vAvailableDevices[0];
  uint32_t nNbDeviceExtensions = 0;
  CHK_VK_SUCCESS(vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &nNbDeviceExtensions, nullptr));

  std::vector<VkExtensionProperties> vExtensionProperties(nNbDeviceExtensions);
  CHK_VK_SUCCESS(vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &nNbDeviceExtensions, vExtensionProperties.data()));

  //
  //  Getting features and properties of a physical device
  //

  VkPhysicalDeviceFeatures vkDeviceFeatures;
  VkPhysicalDeviceProperties vkDeviceProperties;

  vkGetPhysicalDeviceFeatures(vkPhysicalDevice, &vkDeviceFeatures);
  vkGetPhysicalDeviceProperties(vkPhysicalDevice, &vkDeviceProperties);

  std::cout << "Device Name: " << vkDeviceProperties.deviceName << std::endl;
  std::cout << "Device Type: " << vkDeviceProperties.deviceType << std::endl;

  std::cout << "Program ended successfully !" << std::endl;

  return 0;
}