#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <utility>

#include "../Logger.h"

namespace Covid
{
    namespace Graphics
    {
    
        class Utils
        {
        public:
            static std::vector<VkExtensionProperties> QueryAvailableExtensions(bool shouldLog = false)
            {
                uint32_t availableExtensionCount = 0;
                vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
                std::vector<VkExtensionProperties> extensions(availableExtensionCount);
                vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensions.data());

                if (shouldLog)
                {
                    Logger::EngineTrace("Available Vulkan Extensions: {}", availableExtensionCount);
                    for each (auto extension in extensions)
                    {
                        Logger::EngineTrace("{}", extension.extensionName);
                    }
                    Logger::EngineTrace("");
                }
                return extensions;
            }

            static std::pair<uint32_t, std::vector<const char*>> QueryRequiredExtensions(bool shouldLog = false)
            {
                uint32_t glfwExtensionCount = 0;;
                const char** glfwExtensions;

                glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

                std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

                if(Utils::ValidationLayersEnabled())
                {
                    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                }

                if (shouldLog)
                {
                    Logger::EngineTrace("Required Vulkan Extensions: {}", extensions.size());
                    for (size_t i = 0; i < extensions.size(); i++)
                    {
                        const char* extensionName = extensions[i];
                        Logger::EngineTrace("{}", extensionName);
                    }
                    Logger::EngineTrace("");
                }


                return std::make_pair(extensions.size(), extensions);
            }

            static bool QueryRequiredExtensionsAvailable(std::pair<uint32_t, std::vector<const char*>> requiredExtensions, std::vector<VkExtensionProperties> availableExtensions)
            {
                bool success = true;
                for (size_t i = 0; i < requiredExtensions.first; i++)
                {
                    if (std::find_if(availableExtensions.begin(), availableExtensions.end(), [requiredExtensions, i](VkExtensionProperties props) { return std::strcmp(props.extensionName, requiredExtensions.second[i]); }) == availableExtensions.end())
                    {
                        Logger::EngineError("Required Extension: {} not available!", requiredExtensions.second[i]);
                        success = false;
                    }
                }
                return success;
            }

            static bool QueryValidationLayerSupport(std::vector<const char*> validationLayers)
            {
                uint32_t layerCount = 0;
                vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
                std::vector<VkLayerProperties> availableLayers(layerCount);
                vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

                bool success = true;
                for (const char* layerName : validationLayers) {
                    if (std::find_if(availableLayers.begin(), availableLayers.end(), [layerName](VkLayerProperties props) { return std::strcmp(props.layerName, layerName); }) == availableLayers.end())
                    {
                        Logger::EngineError("Required Validation Layer: {} not available!", layerName);
                        success = false;
                    }
                }
                return success;
            }


            static bool ValidationLayersEnabled()
            {
#ifdef DEBUG
                return true;
#else
                return false;
#endif
            }

            static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData)
            {
                if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
                {
                    Logger::EngineTrace(pCallbackData->pMessage);
                }
                else if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
                {
                    Logger::EngineInfo(pCallbackData->pMessage);
                }
                else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
                {
                    Logger::EngineWarn(pCallbackData->pMessage);
                }
                else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
                {
                    Logger::EngineError(pCallbackData->pMessage);
                }
                return VK_FALSE;
            }

            static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
                auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
                if (func != nullptr) 
                {
                    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
                }
                else 
                {
                    return VK_ERROR_EXTENSION_NOT_PRESENT;
                }
            }

            static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
                auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
                if (func != nullptr) 
                {
                    func(instance, debugMessenger, pAllocator);
                }
            }

            static VkDebugUtilsMessengerCreateInfoEXT PopulateDebugMessengerStruct(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
            {
                createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                createInfo.pfnUserCallback = Utils::VulkanDebugCallback;
                createInfo.pUserData = nullptr;
                return createInfo;
            }

            static std::string GetDeviceTypeName(VkPhysicalDeviceType type)
            {
                switch (type)
                {
                case VK_PHYSICAL_DEVICE_TYPE_OTHER:
                    return "Other";
                case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                    return "Integrated GPU";
                case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                    return "Discrete GPU";
                case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                    return "Virtual GPU";
                case VK_PHYSICAL_DEVICE_TYPE_CPU:
                    return "CPU";
                }
                return "Unknown";
            }

            static void LogDeviceProperties(VkPhysicalDevice device)
            {
                VkPhysicalDeviceProperties properties;
                vkGetPhysicalDeviceProperties(device, &properties);

                VkPhysicalDeviceMemoryProperties memoryProps;
                vkGetPhysicalDeviceMemoryProperties(device, &memoryProps);


                Logger::EngineInfo("Selected GPU:");
                Logger::EngineInfo("     Type:    {}", Utils::GetDeviceTypeName(properties.deviceType));
                Logger::EngineInfo("     Name:    {}", properties.deviceName);

                uint64_t totalMemory = 0;
                for (uint32_t i = 0; i < memoryProps.memoryHeapCount; i++)
                {
                    VkMemoryHeap heap = memoryProps.memoryHeaps[i];
                    if(heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
                    {
                        totalMemory += heap.size;
                    }
                }
                int memoryGB = totalMemory / 1000000000;
                Logger::EngineInfo("     VRAM:    {} GB", memoryGB);
            }

            static QueueFamilies FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
            {
                QueueFamilies indices = QueueFamilies();

                uint32_t queueFamilyCount = 0;
                vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

                std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
                vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

                for (int i = 0; i < queueFamilies.size(); i++)
                {
                    if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    {
                        indices.graphicsFamily = i;
                    }

                    VkBool32 presentSupport = false;
                    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
                    if (presentSupport)
                    {
                        indices.presentFamily = i;
                    }

                    if (indices.IsComplete())
                    {
                        break;
                    }
                }

                return indices;
            }


        };
    }
}