#include "SwapChainBuilder.h"

#include "../Logger.h"
#include "../Window/Window.h"
#include "Device.h"
#include "SwapChain.h"
#include "Utils.h"

#include "GLFW/glfw3.h"

namespace Covid
{
    namespace Graphics
    {
        SwapChainBuilder::SwapChainBuilder()
        {
        }

        SwapChainBuilder::~SwapChainBuilder()
        {
        }

        SwapChainBuilder& Covid::Graphics::SwapChainBuilder::SetWindow(Window* window)
        {
            m_window = window;
            return *this;
        }

        SwapChainBuilder& Covid::Graphics::SwapChainBuilder::SetDevice(Device* device)
        {
            m_device = device;
            return *this;
        }

        SwapChain* Covid::Graphics::SwapChainBuilder::Build()
        {
            if(m_device == nullptr || m_window == nullptr)
            {
                Logger::EngineCritical("Both Device & Window must be set before SwapChain creation!");
            }   

            SwapChain* swapChain = new SwapChain();

            SwapChainSupportDetails details = SwapChain::QuerySwapChainSupport(m_device, m_device->m_device);
            swapChain->m_surfaceFormat = ChooseSwapSurfaceFormat(details.formats);
            swapChain->m_presentMode = ChooseSwapPresentMode(details.presentModes);
            swapChain->m_swapExtent = ChooseSwapExtent(details.capabilities);

            swapChain->m_imageCount = details.capabilities.minImageCount + 1;
            if (details.capabilities.maxImageCount > 0 && swapChain->m_imageCount > details.capabilities.maxImageCount) {
                swapChain->m_imageCount = details.capabilities.maxImageCount;
            }

            VkSwapchainCreateInfoKHR createInfo = VkSwapchainCreateInfoKHR();
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = m_device->m_surface;

            createInfo.minImageCount = swapChain->m_imageCount;
            createInfo.imageFormat = swapChain->m_surfaceFormat.format;
            createInfo.imageColorSpace = swapChain->m_surfaceFormat.colorSpace;
            createInfo.imageExtent = swapChain->m_swapExtent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            QueueFamilies indices = Utils::FindQueueFamilies(m_device->m_device, m_device->m_surface);
            uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            if (indices.graphicsFamily != indices.presentFamily) {
                createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                createInfo.queueFamilyIndexCount = 2;
                createInfo.pQueueFamilyIndices = queueFamilyIndices;
            }
            else {
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                createInfo.queueFamilyIndexCount = 0; // Optional
                createInfo.pQueueFamilyIndices = nullptr; // Optional
            }

            createInfo.preTransform = details.capabilities.currentTransform;
            createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

            createInfo.presentMode = swapChain->m_presentMode;
            createInfo.clipped = VK_TRUE;

            createInfo.oldSwapchain = VK_NULL_HANDLE;

            if(vkCreateSwapchainKHR(m_device->m_logicalDevice, &createInfo, nullptr, &swapChain->m_swapChain) != VK_SUCCESS)
            {
                Logger::EngineCritical("Failed to create swap chain!");
            }

            swapChain->m_logicalDevice = m_device->m_logicalDevice;

            vkGetSwapchainImagesKHR(m_device->m_logicalDevice, swapChain->m_swapChain, &swapChain->m_imageCount, nullptr);
            swapChain->m_swapChainImages.resize(swapChain->m_imageCount);
            vkGetSwapchainImagesKHR(m_device->m_logicalDevice, swapChain->m_swapChain, &swapChain->m_imageCount, swapChain->m_swapChainImages.data());

            return swapChain;
        }

        VkSurfaceFormatKHR SwapChainBuilder::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
        {
            for(const VkSurfaceFormatKHR availableFormat : availableFormats)
            {
                if(availableFormat.format == VK_FORMAT_R8G8B8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                {
                    return availableFormat;
                }
            }

            //TODO: implement a ranking system for available surface formats
            return availableFormats[0];
        }

        VkPresentModeKHR SwapChainBuilder::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
        {
            for(const VkPresentModeKHR presentMode : availablePresentModes)
            {
                if(presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                {
                    return presentMode;
                }
            }
            return VK_PRESENT_MODE_FIFO_KHR;
        }

        VkExtent2D SwapChainBuilder::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
        {
            if(capabilities.currentExtent.width != UINT32_MAX)
            {
                return capabilities.currentExtent;
            }
            else
            {
                int width, height;
                glfwGetFramebufferSize(m_window->m_window, &width, &height);

                VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
                };

                actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
                actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

                return actualExtent;
            }
        }

        void SwapChainBuilder::CreateImageViews(SwapChain* swapChain)
        {
            swapChain->m_swapChainImageViews.resize(swapChain->m_swapChainImages.size());
            for (size_t i = 0; i < swapChain->m_swapChainImages.size(); i++)
            {
                VkImageViewCreateInfo createInfo = VkImageViewCreateInfo();
                createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                createInfo.image = swapChain->m_swapChainImages[i];

                createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                createInfo.format = swapChain->m_surfaceFormat.format;

                createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

                createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel = 0;
                createInfo.subresourceRange.levelCount = 1;
                createInfo.subresourceRange.baseArrayLayer = 0;
                createInfo.subresourceRange.layerCount = 1;

                if (vkCreateImageView(m_device->m_logicalDevice, &createInfo, nullptr, &swapChain->m_swapChainImageViews[i]) != VK_SUCCESS) {
                    Logger::EngineCritical("Failed to create Image Views in SwapChain");
                }
            }

        }
    }
}


