#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Covid
{
    class Window;

    namespace Graphics
    {
        class SwapChain;
        class Device;

        class SwapChainBuilder
        {
        public:
            SwapChainBuilder();
            ~SwapChainBuilder();

            SwapChainBuilder& SetWindow(Window* window);
            SwapChainBuilder& SetDevice(Device* device);

            SwapChain* Build();

        private:
            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            void CreateImageViews(SwapChain* swapChain);

        private:
            Window* m_window;
            Device* m_device;
        };
    }
}