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

        private:
            Device();

        public:
            ~Device();

        public:
            static DeviceBuilder Create();

        private:
            VkInstance m_instance;
            VkDebugUtilsMessengerEXT m_debugMessenger;
        };
    }
}