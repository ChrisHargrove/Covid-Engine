#include "DeviceBuilder.h"

#include <vulkan/vulkan.h>
#include <map>
#include <set>

#include "../Window/Window.h"
#include "Utils.h"
#include "Device.h"

namespace Covid
{
    namespace Graphics
    {
        DeviceBuilder::DeviceBuilder() :
            m_appName("Default App Name"),
            m_appVersion(VK_MAKE_VERSION(0,0,1)),
            m_showDeviceInfo(false),
            m_showInstanceInfo(false),
            m_requiredFeatures(std::vector<DeviceFeature>(1))
        {
        }

        DeviceBuilder::~DeviceBuilder()
        {
        }

        DeviceBuilder& DeviceBuilder::SetWindow(Window* window)
        {
            m_window = window;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetApplicationName(const std::string& appName)
        {
            m_appName = appName;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetApplicationVersion(int major, int minor, int patch)
        {
            m_appVersion = VK_MAKE_VERSION(major, minor, patch);
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetShowInstanceInfo(bool showIntanceInfo)
        {
            m_showInstanceInfo = showIntanceInfo;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetShowDeviceInfo(bool showDeviceInfo)
        {
            m_showDeviceInfo = showDeviceInfo;
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetRequiredFeature(DeviceFeature feature)
        {
            m_requiredFeatures.push_back(feature);
            return *this;
        }

        DeviceBuilder& DeviceBuilder::RequiresSwapChain(bool needSwapChain)
        {
            if(needSwapChain)
            {
                m_requiredExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
                m_needsSwapChain = needSwapChain;
            }
            return *this;
        }

        DeviceBuilder& DeviceBuilder::SetRequiredExtension(const std::string& extensionName)
        {
            m_requiredExtensions.push_back(extensionName.c_str());
            return *this;
        }

        Device* DeviceBuilder::Build()
        {
            if(!m_window)
            {
                Logger::EngineCritical("Cannot Create Vulkan Device Without Window!");
                return nullptr;
            }

            m_device = new Device();

            CreateInstance(m_device);
            SetupDebugMessenger(m_device);
            CreateSurface(m_device);
            PickPhysicalDevice(m_device);
            CreateLogicalDevice(m_device);

            return m_device;
        }

        void DeviceBuilder::CreateInstance(Device* device)
        {
            if(Utils::ValidationLayersEnabled() && !Utils::QueryValidationLayerSupport(m_validationLayers))
            {
                Logger::EngineCritical("Not all required validaation layers available!");
            }

            VkApplicationInfo info = VkApplicationInfo();
            info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            info.pApplicationName = m_appName.c_str();
            info.applicationVersion = m_appVersion;
            info.pEngineName = "Covid Engine";
            info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
            info.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo = VkInstanceCreateInfo();
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &info;

            std::vector<VkExtensionProperties> availableExtensions = Utils::QueryAvailableExtensions(m_showInstanceInfo);
            std::pair<uint32_t, std::vector<const char*>> requiredExtensions = Utils::QueryRequiredExtensions(m_showInstanceInfo);
            if(!Utils::QueryRequiredExtensionsAvailable(requiredExtensions, availableExtensions))
            {
                Logger::EngineCritical("Not all required extensions available!");
            }

            createInfo.enabledExtensionCount = requiredExtensions.first;
            createInfo.ppEnabledExtensionNames = requiredExtensions.second.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = VkDebugUtilsMessengerCreateInfoEXT();
            if (Utils::ValidationLayersEnabled())
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
                createInfo.ppEnabledLayerNames = m_validationLayers.data();

                Utils::PopulateDebugMessengerStruct(debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }
            else
            {
                createInfo.enabledLayerCount = 0;
            }

            if (vkCreateInstance(&createInfo, nullptr, &device->m_instance) != VK_SUCCESS) {
                Logger::EngineCritical("Failed to create Vulkan Instance");
            }
        }

        void DeviceBuilder::SetupDebugMessenger(Device* device)
        {
            if (!Utils::ValidationLayersEnabled()) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo = VkDebugUtilsMessengerCreateInfoEXT();
            Utils::PopulateDebugMessengerStruct(createInfo);

            if(Utils::CreateDebugUtilsMessengerEXT(device->m_instance, &createInfo, nullptr, &device->m_debugMessenger) != VK_SUCCESS)
            {
                Logger::EngineCritical("Failed to create Vulkan Debug Messenger");
            }
        }

        void DeviceBuilder::CreateSurface(Device* device)
        {
            if(glfwCreateWindowSurface(device->m_instance, m_window->m_window, nullptr, &device->m_surface) != VK_SUCCESS)
            {
                Logger::EngineCritical("Failed to create window surface!");
            }
        }

        void DeviceBuilder::PickPhysicalDevice(Device* device)
        {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(device->m_instance, &deviceCount, nullptr);

            if(deviceCount == 0)
            {
                Logger::EngineCritical("No Vulkan capable devices found...");
            }
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(device->m_instance, &deviceCount, devices.data());

            std::multimap<int, VkPhysicalDevice> deviceCandidates;

            for (const VkPhysicalDevice physicalDevice : devices)
            {
                int suitability = RateDeviceSuitability(physicalDevice);
                deviceCandidates.insert(std::make_pair(suitability, physicalDevice));
            }

            if(deviceCandidates.rbegin()->first > 0)
            {
                device->m_device = deviceCandidates.rbegin()->second;
                if(m_showDeviceInfo)
                {
                    Utils::LogDeviceProperties(device->m_device);
                }
            }
            else
            {
                Logger::EngineCritical("Failed to find a suitable GPU!");
            }

        }

        int DeviceBuilder::RateDeviceSuitability(VkPhysicalDevice device)
        {
            int score = 0;
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);
            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(device, &features);

            if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) 
            {
                score += 1000;
            }

            score += properties.limits.maxImageDimension2D;

            for (DeviceFeature feature : m_requiredFeatures)
            {
                if(!HasFeature(feature, features))
                {
                    return 0;
                }
            }

            for(std::string extension : m_requiredExtensions)
            {
                if(!HasExtension(device, extension))
                {
                    return 0;
                }
            }

            if(m_needsSwapChain)
            {
                SwapChainSupportDetails swapDetails = QuerySwapChainSupport(m_device, device);
                if(swapDetails.formats.empty() || swapDetails.presentModes.empty())
                {
                    return 0;
                }
            }

            if(!IsDeviceSuitable(device))
            {
                return 0;
            }

            return score;
        }

        bool DeviceBuilder::HasFeature(DeviceFeature feature, VkPhysicalDeviceFeatures deviceFeatures)
        {
            switch (feature)
            {
            case Covid::Graphics::DeviceFeature::RobustBufferAccess:
                return deviceFeatures.robustBufferAccess;
            case Covid::Graphics::DeviceFeature::FullDrawIndexUint32:
                return deviceFeatures.fullDrawIndexUint32;
            case Covid::Graphics::DeviceFeature::ImageCubeArray:
                return deviceFeatures.imageCubeArray;
            case Covid::Graphics::DeviceFeature::IndependentBlend:
                return deviceFeatures.independentBlend;
            case Covid::Graphics::DeviceFeature::GeometryShader:
                return deviceFeatures.geometryShader;
            case Covid::Graphics::DeviceFeature::TesselationShader:
                return deviceFeatures.tessellationShader;
            case Covid::Graphics::DeviceFeature::SampleRateShading:
                return deviceFeatures.sampleRateShading;
            case Covid::Graphics::DeviceFeature::DualSourceBlend:
                return deviceFeatures.dualSrcBlend;
            case Covid::Graphics::DeviceFeature::LogicOp:
                return deviceFeatures.logicOp;
            case Covid::Graphics::DeviceFeature::MultiDrawIndirect:
                return deviceFeatures.multiDrawIndirect;
            case Covid::Graphics::DeviceFeature::DrawIndirectFirstInstance:
                return deviceFeatures.drawIndirectFirstInstance;
            case Covid::Graphics::DeviceFeature::DepthClamp:
                return deviceFeatures.depthClamp;
            case Covid::Graphics::DeviceFeature::DepthBiasClamp:
                return deviceFeatures.depthBiasClamp;
            case Covid::Graphics::DeviceFeature::FillModeNonSolid:
                return deviceFeatures.fillModeNonSolid;
            case Covid::Graphics::DeviceFeature::DepthBounds:
                return deviceFeatures.depthBounds;
            case Covid::Graphics::DeviceFeature::WideLines:
                return deviceFeatures.wideLines;
            case Covid::Graphics::DeviceFeature::LargePoints:
                return deviceFeatures.largePoints;
            case Covid::Graphics::DeviceFeature::AlphaToOne:
                return deviceFeatures.alphaToOne;
            case Covid::Graphics::DeviceFeature::MultiViewport:
                return deviceFeatures.multiViewport;
            case Covid::Graphics::DeviceFeature::SamplerAnisotropy:
                return deviceFeatures.samplerAnisotropy;
            case Covid::Graphics::DeviceFeature::TextureCompressionETC2:
                return deviceFeatures.textureCompressionETC2;
            case Covid::Graphics::DeviceFeature::TextureCompressionASTC_LDR:
                return deviceFeatures.textureCompressionASTC_LDR;
            case Covid::Graphics::DeviceFeature::TextureCompressionBC:
                return deviceFeatures.textureCompressionBC;
            case Covid::Graphics::DeviceFeature::OcclusionQueryPrecise:
                return deviceFeatures.occlusionQueryPrecise;
            case Covid::Graphics::DeviceFeature::PipelineStatisticsQuery:
                return deviceFeatures.pipelineStatisticsQuery;
            case Covid::Graphics::DeviceFeature::VertexPipelineStoresAnddAtomics:
                return deviceFeatures.vertexPipelineStoresAndAtomics;
            case Covid::Graphics::DeviceFeature::FragmentStoresAndAtomics:
                return deviceFeatures.fragmentStoresAndAtomics;
            case Covid::Graphics::DeviceFeature::ShaderTessellationAndGeometryPointSize:
                return deviceFeatures.shaderTessellationAndGeometryPointSize;
            case Covid::Graphics::DeviceFeature::ShaderImageGatherExtended:
                return deviceFeatures.shaderImageGatherExtended;
            case Covid::Graphics::DeviceFeature::ShaderStorageImageExtendedFormats:
                return deviceFeatures.shaderStorageImageExtendedFormats;
            case Covid::Graphics::DeviceFeature::ShaderStorageImageMultisample:
                return deviceFeatures.shaderStorageImageMultisample;
            case Covid::Graphics::DeviceFeature::ShaderStorageImageReadWithoutFormat:
                return deviceFeatures.shaderStorageImageReadWithoutFormat;
            case Covid::Graphics::DeviceFeature::ShaderStorageImageWriteWithoutFormat:
                return deviceFeatures.shaderStorageImageWriteWithoutFormat;
            case Covid::Graphics::DeviceFeature::ShaderUniformBufferArrayDynamicIndexing:
                return deviceFeatures.shaderUniformBufferArrayDynamicIndexing;
            case Covid::Graphics::DeviceFeature::ShaderSampledImageArrayDynamicIndexing:
                return deviceFeatures.shaderSampledImageArrayDynamicIndexing;
            case Covid::Graphics::DeviceFeature::ShaderStorageBufferArrayDynamicIndexing:
                return deviceFeatures.shaderStorageBufferArrayDynamicIndexing;
            case Covid::Graphics::DeviceFeature::ShaderStorageImageArrayDynamicIndexing:
                return deviceFeatures.shaderStorageImageArrayDynamicIndexing;
            case Covid::Graphics::DeviceFeature::ShaderClipDistance:
                return deviceFeatures.shaderCullDistance;
            case Covid::Graphics::DeviceFeature::ShaderCullDistance:
                return deviceFeatures.shaderCullDistance;
            case Covid::Graphics::DeviceFeature::ShaderFloat64:
                return deviceFeatures.shaderFloat64;
            case Covid::Graphics::DeviceFeature::ShaderInt64:
                return deviceFeatures.shaderInt64;
            case Covid::Graphics::DeviceFeature::ShaderInt16:
                return deviceFeatures.shaderInt16;
            case Covid::Graphics::DeviceFeature::ShaderResourceResidency:
                return deviceFeatures.shaderResourceResidency;
            case Covid::Graphics::DeviceFeature::ShaderResourceMinLOD:
                return deviceFeatures.shaderResourceMinLod;
            case Covid::Graphics::DeviceFeature::SparseBinding:
                return deviceFeatures.sparseBinding;
            case Covid::Graphics::DeviceFeature::SparseResidencyBuffer:
                return deviceFeatures.sparseResidencyBuffer;
            case Covid::Graphics::DeviceFeature::SparseResidencyImage2D:
                return deviceFeatures.sparseResidencyImage2D;
            case Covid::Graphics::DeviceFeature::SparseResidencyImage3D:
                return deviceFeatures.sparseResidencyImage3D;
            case Covid::Graphics::DeviceFeature::SparseResidency2Samples:
                return deviceFeatures.sparseResidency2Samples;
            case Covid::Graphics::DeviceFeature::SparseResidency4Samples:
                return deviceFeatures.sparseResidency4Samples;
            case Covid::Graphics::DeviceFeature::SparseResidency8Samples:
                return deviceFeatures.sparseResidency8Samples;
            case Covid::Graphics::DeviceFeature::SparseResidency16Samples:
                return deviceFeatures.sparseResidency16Samples;
            case Covid::Graphics::DeviceFeature::SparseResidencyAliased:
                return deviceFeatures.sparseResidencyAliased;
            case Covid::Graphics::DeviceFeature::VariableMultisampleRate:
                return deviceFeatures.variableMultisampleRate;
            case Covid::Graphics::DeviceFeature::InheritedQueries:
                return deviceFeatures.inheritedQueries;
            default:
                break;
            }
            return false;
        }

        bool DeviceBuilder::HasExtension(VkPhysicalDevice device, const std::string& extensionName)
        {
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

            std::set<std::string> requiredExtensions(m_requiredExtensions.begin(), m_requiredExtensions.end());

            for (const auto& extension : availableExtensions) {
                requiredExtensions.erase(extension.extensionName);
            }

            return requiredExtensions.empty();
        }

        bool DeviceBuilder::IsDeviceSuitable(VkPhysicalDevice device)
        {
            QueueFamilies indices = Utils::FindQueueFamilies(device, m_device->m_surface);
            return indices.IsComplete();
        }

        void DeviceBuilder::CreateLogicalDevice(Device* device)
        {
            QueueFamilies indices = Utils::FindQueueFamilies(device->m_device, device->m_surface);

            std::vector<VkDeviceQueueCreateInfo> queueInfoList;
            std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            float queuePriority = 1.0f;
            for(uint32_t queueFamily : uniqueQueueFamilies)
            {
                VkDeviceQueueCreateInfo queueInfo = VkDeviceQueueCreateInfo();
                queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueInfo.queueFamilyIndex = queueFamily;
                queueInfo.queueCount = 1;
                queueInfo.pQueuePriorities = &queuePriority;
                queueInfoList.push_back(queueInfo);
            }
            
            VkPhysicalDeviceFeatures deviceFeatures = VkPhysicalDeviceFeatures();

            VkDeviceCreateInfo deviceInfo = VkDeviceCreateInfo();
            deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            deviceInfo.pQueueCreateInfos = queueInfoList.data();
            deviceInfo.queueCreateInfoCount = queueInfoList.size();
            deviceInfo.pEnabledFeatures = &deviceFeatures;
            deviceInfo.enabledExtensionCount = m_requiredExtensions.size();
            deviceInfo.ppEnabledExtensionNames = m_requiredExtensions.data();

            if(Utils::ValidationLayersEnabled())
            {
                deviceInfo.enabledLayerCount = m_validationLayers.size();
                deviceInfo.ppEnabledLayerNames = m_validationLayers.data();
            }
            else
            {
                deviceInfo.enabledLayerCount = 0;
            }

            if(vkCreateDevice(device->m_device, &deviceInfo, nullptr, &device->m_logicalDevice) != VK_SUCCESS)
            {
                Logger::EngineCritical("Logical Device Creation Failed!");
            }

            vkGetDeviceQueue(device->m_logicalDevice, indices.graphicsFamily.value(), 0, &device->m_graphicsQueue);
            vkGetDeviceQueue(device->m_logicalDevice, indices.presentFamily.value(), 0, &device->m_presentQueue);
        }

        SwapChainSupportDetails DeviceBuilder::QuerySwapChainSupport(Device* device, VkPhysicalDevice physicalDevice)
        {
            return SwapChain::QuerySwapChainSupport(device, physicalDevice);
        }
        
    }
}