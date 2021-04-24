#pragma once

#include <string>
#include <vector>

namespace Covid
{
    class Window;

    namespace Graphics
    {
        class Device;

        class DeviceBuilder
        {
        public:
            DeviceBuilder();
            ~DeviceBuilder();

            DeviceBuilder& SetWindow(Window* window);
            DeviceBuilder& SetApplicationName(const std::string& appName);
            DeviceBuilder& SetApplicationVersion(int major, int minor, int patch);
            DeviceBuilder& SetShowDeviceInfo(bool showDeviceInfo);

            Device* Build();

        private:
            void CreateInstance(Device* device);
            void SetupDebugMessenger(Device* device);

        private:
            Window* m_window;

            std::string m_appName;
            uint32_t m_appVersion;
            bool m_showDeviceInfo;

            const std::vector<const char*> m_validationLayers = {
                   "VK_LAYER_KHRONOS_validation"
            };


        };
    }
}
