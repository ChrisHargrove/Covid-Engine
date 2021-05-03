#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "../Logger.h"
#include "SwapChainBuilder.h"

namespace Covid
{
    namespace Graphics
    {
        class Device;

        struct SwapChainSupportDetails
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        class SwapChain
        {
            friend SwapChainBuilder;

        private:
            SwapChain();

        public:
            ~SwapChain();

        public:
            static SwapChainSupportDetails QuerySwapChainSupport(Device* device, VkPhysicalDevice physicalDevice);
            static SwapChainBuilder Create();

        private:
            VkDevice m_logicalDevice;
            VkSwapchainKHR m_swapChain;

            VkSurfaceFormatKHR m_surfaceFormat;
            VkPresentModeKHR m_presentMode;
            VkExtent2D m_swapExtent;

            uint32_t m_imageCount;
            std::vector<VkImage> m_swapChainImages;
            std::vector<VkImageView> m_swapChainImageViews;


        };
    }
}