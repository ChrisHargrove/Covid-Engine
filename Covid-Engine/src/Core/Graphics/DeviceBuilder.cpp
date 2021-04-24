#include "DeviceBuilder.h"

#include <vulkan/vulkan.h>

#include "../Window/Window.h"
#include "Utils.h"
#include "Device.h"

namespace Covid
{
    namespace Graphics
    {
        DeviceBuilder::DeviceBuilder() :
            m_appName("Default App Name"),
            m_appVersion(VK_MAKE_VERSION(0,0,1)),
            m_showDeviceInfo(false)
        {
        }

        DeviceBuilder::~DeviceBuilder()
        {
        }

        DeviceBuilder& DeviceBuilder::SetWindow(Window* window)
        {
            m_window = window;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetApplicationName(const std::string& appName)
        {
            m_appName = appName;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetApplicationVersion(int major, int minor, int patch)
        {
            m_appVersion = VK_MAKE_VERSION(major, minor, patch);
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetShowDeviceInfo(bool showDebug)
        {
            m_showDeviceInfo = showDebug;
            return *this;
        }

        Device* DeviceBuilder::Build()
        {
            if(!m_window)
            {
                Logger::EngineCritical("Cannot Create Vulkan Device Without Window!");
                return nullptr;
            }

            Device* device = new Device();

            CreateInstance(device);
            SetupDebugMessenger(device);

            return device;
        }

        void DeviceBuilder::CreateInstance(Device* device)
        {
            if(Utils::ValidationLayersEnabled() && !Utils::QueryValidationLayerSupport(m_validationLayers))
            {
                Logger::EngineCritical("Not all required validaation layers available!");
            }

            VkApplicationInfo info = VkApplicationInfo();
            info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            info.pApplicationName = m_appName.c_str();
            info.applicationVersion = m_appVersion;
            info.pEngineName = "Covid Engine";
            info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
            info.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo = VkInstanceCreateInfo();
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &info;

            std::vector<VkExtensionProperties> availableExtensions = Utils::QueryAvailableExtensions(m_showDeviceInfo);
            std::pair<uint32_t, std::vector<const char*>> requiredExtensions = Utils::QueryRequiredExtensions(m_showDeviceInfo);
            if(!Utils::QueryRequiredExtensionsAvailable(requiredExtensions, availableExtensions))
            {
                Logger::EngineCritical("Not all required extensions available!");
            }

            createInfo.enabledExtensionCount = requiredExtensions.first;
            createInfo.ppEnabledExtensionNames = requiredExtensions.second.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = VkDebugUtilsMessengerCreateInfoEXT();
            if (Utils::ValidationLayersEnabled())
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
                createInfo.ppEnabledLayerNames = m_validationLayers.data();

                Utils::PopulateDebugMessengerStruct(debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }
            else
            {
                createInfo.enabledLayerCount = 0;
            }

            if (vkCreateInstance(&createInfo, nullptr, &device->m_instance) != VK_SUCCESS) {
                Logger::EngineCritical("Failed to create Vulkan Instance");
            }
        }

        void DeviceBuilder::SetupDebugMessenger(Device* device)
        {
            if (!Utils::ValidationLayersEnabled) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo = VkDebugUtilsMessengerCreateInfoEXT();
            Utils::PopulateDebugMessengerStruct(createInfo);

            if(Utils::CreateDebugUtilsMessengerEXT(device->m_instance, &createInfo, nullptr, &device->m_debugMessenger) != VK_SUCCESS)
            {
                Logger::EngineCritical("Failed to create Vulkan Debug Messenger");
            }
        }

        
    }
}