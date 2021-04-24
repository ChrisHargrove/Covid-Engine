#include "Device.h"

#include "Utils.h"

namespace Covid
{
    namespace Graphics
    {
        Device::Device()
        {
        }

        Device::~Device()
        {
            if(Utils::ValidationLayersEnabled)
            {
                Utils::DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
            }
            vkDestroyInstance(m_instance, nullptr);
        }

        DeviceBuilder Device::Create()
        {
            return DeviceBuilder();
        }
    }
}