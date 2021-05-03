#pragma once

#include "Window/Window.h"
#include "Graphics/Device.h"
#include "../Utilities/Time.h"

namespace Covid
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void Init() = 0;

        void Run();

        virtual void Update() = 0;
        virtual void FixedUpdate() = 0;

        virtual void Shutdown() = 0;

    protected:
        Window* m_window;
        Input* m_input;
        Time* m_time;

        Graphics::Device* m_device;
        Graphics::SwapChain* m_swapChain;
    };

    //To be defined by the user.
    Application* CreateApplication();

}