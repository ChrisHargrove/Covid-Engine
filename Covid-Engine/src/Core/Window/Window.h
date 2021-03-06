#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <string>

#include "../Logger.h"
#include "WindowBuilder.h"
#include "../Input/InputBuilder.h"
#include "../Graphics/DeviceBuilder.h"

namespace Covid
{
    class Window
    {
        friend WindowBuilder;
        friend InputBuilder;
        friend Graphics::DeviceBuilder;
        friend Graphics::SwapChainBuilder;
    
    private:
        Window();

    public:
        ~Window();

    public:
        static void Init();

        static void Shutdown();

        static WindowBuilder Create();

        static bool ShouldClose(Window* instance);

        void SetSize(int width, int height);

        void GetSize(int* width, int* height);

    private:
        static void OnError(int errorCode, const char* description);


    private:
        GLFWwindow* m_window;

    };

}


