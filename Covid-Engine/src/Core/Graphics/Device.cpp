#include "Device.h"

#include "Utils.h"

namespace Covid
{
    namespace Graphics
    {
        Device::Device() :
            m_device(VK_NULL_HANDLE)
        {
        }

        Device::~Device()
        {
            vkDestroyDevice(m_logicalDevice, nullptr);
            if(Utils::ValidationLayersEnabled)
            {
                Utils::DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
            }
            vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
            vkDestroyInstance(m_instance, nullptr);
        }

        DeviceBuilder Device::Create()
        {
            return DeviceBuilder();
        }
    }
}