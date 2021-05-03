#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "DeviceBuilder.h"

namespace Covid
{
    namespace Graphics
    {
        class Device
        {
            friend DeviceBuilder;
            friend SwapChain;
            friend SwapChainBuilder;

        private:
            Device();

        public:
            ~Device();

        public:
            static DeviceBuilder Create();

        private:
            VkInstance m_instance;
            VkPhysicalDevice m_device;
            VkDevice m_logicalDevice;
            VkDebugUtilsMessengerEXT m_debugMessenger;
            VkSurfaceKHR m_surface;

            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
        };
    }
}