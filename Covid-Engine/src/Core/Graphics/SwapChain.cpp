#include "SwapChain.h"

#include "Device.h"

namespace Covid
{
    namespace Graphics
    {
        SwapChain::SwapChain()
        {
        }

        SwapChain::~SwapChain()
        {
            for (VkImageView imageView : m_swapChainImageViews) {
                vkDestroyImageView(m_logicalDevice, imageView, nullptr);
            }
            vkDestroySwapchainKHR(m_logicalDevice, m_swapChain, nullptr);
        }

        SwapChainSupportDetails SwapChain::QuerySwapChainSupport(Device* device, VkPhysicalDevice physicalDevice)
        {
            SwapChainSupportDetails details = SwapChainSupportDetails();

            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, device->m_surface, &details.capabilities);

            uint32_t formatCount = 0;
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, device->m_surface, &formatCount, nullptr);

            if (formatCount != 0)
            {
                details.formats.resize(formatCount);
                vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, device->m_surface, &formatCount, details.formats.data());
            }

            uint32_t presentModeCount = 0;
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, device->m_surface, &presentModeCount, nullptr);
            if (presentModeCount != 0)
            {
                details.presentModes.resize(presentModeCount);
                vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, device->m_surface, &presentModeCount, details.presentModes.data());
            }

            return details;
        }

        SwapChainBuilder SwapChain::Create()
        {
            return SwapChainBuilder();
        }
    }
}

