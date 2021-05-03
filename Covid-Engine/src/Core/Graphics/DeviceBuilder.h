#pragma once

#include <string>
#include <vector>
#include <optional>
#include "vulkan/vulkan.h"

#include "DeviceFeatures.h"
#include "SwapChain.h"

namespace Covid
{
    class Window;

    namespace Graphics
    {
        class Device;

        struct QueueFamilies
        {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool IsComplete()
            {
                return graphicsFamily.has_value()
                    && presentFamily.has_value();
            }
        };

        class DeviceBuilder
        {
        public:
            DeviceBuilder();
            ~DeviceBuilder();

            DeviceBuilder& SetWindow(Window* window);
            DeviceBuilder& SetApplicationName(const std::string& appName);
            DeviceBuilder& SetApplicationVersion(int major, int minor, int patch);
            DeviceBuilder& SetShowInstanceInfo(bool showInstanceInfo);
            DeviceBuilder& SetShowDeviceInfo(bool showDeviceInfo);

            DeviceBuilder& SetRequiredFeature(DeviceFeature feature);
            DeviceBuilder& SetRequiredExtension(const std::string& extensionName);
            DeviceBuilder& RequiresSwapChain(bool needSwapChain = true);

            Device* Build();

        private:
            void CreateInstance(Device* device);
            void SetupDebugMessenger(Device* device);
            void CreateSurface(Device* device);
            void PickPhysicalDevice(Device* device);
            int RateDeviceSuitability(VkPhysicalDevice device);
            bool IsDeviceSuitable(VkPhysicalDevice device);
            bool HasFeature(DeviceFeature feature, VkPhysicalDeviceFeatures deviceFeatures);

            void CreateLogicalDevice(Device* device);
            bool HasExtension(VkPhysicalDevice device, const std::string& extensionName);
            SwapChainSupportDetails QuerySwapChainSupport(Device* device, VkPhysicalDevice physicalDevice);

        private:
            Window* m_window;
            Device* m_device;

            std::string m_appName;
            uint32_t m_appVersion;
            bool m_showDeviceInfo;
            bool m_showInstanceInfo;
            bool m_needsSwapChain;

            const std::vector<const char*> m_validationLayers = {
                   "VK_LAYER_KHRONOS_validation"
            };

            std::vector<DeviceFeature> m_requiredFeatures;
            std::vector<const char*> m_requiredExtensions;


        };
    }
}
