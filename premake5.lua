workspace "Covid-Engine"
    architecture "x64"
    configurations { "Debug", "Release"}

OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Covid Engine Project Setup
project "Covid-Engine"
    location "Covid-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDirectory .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDirectory .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "C:/VulkanSDK/1.2.170.0/Include",
        "%{prj.name}/infected/spdlog/include",
        "%{prj.name}/infected/glfw-3.3.3/include",
        "%{prj.name}/infected/glm/glm"
    }

    libdirs {
        "C:/VulkanSDK/1.2.170.0/Lib",
        "%{prj.name}/infected/glfw-3.3.3/bin"
    }

    links {
        "vulkan-1.lib",
        "glfw3_mt.lib"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"

project "Quarantine"
    location "Quarantine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDirectory .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDirectory .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "C:/VulkanSDK/1.2.170.0/Include",
        "Covid-Engine/infected/spdlog/include",
        "Covid-Engine/infected/glfw-3.3.3/include",
        "Covid-Engine/infected/glm/glm",

        "Covid-Engine/src"
    }

    libdirs {
        "C:/VulkanSDK/1.2.170.0/Lib",
        "Covid-Engine/infected/glfw-3.3.3/bin"
    }

    links {
        "vulkan-1.lib",
        "glfw3_mt.lib",
        "Covid-Engine"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"