#pragma once

#include "Window/Window.h"
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

        virtual void Shutdown() = 0;

    protected:
        Window* m_window;
        Input* m_input;
        Time* m_time;
    };

    //To be defined by the user.
    Application* CreateApplication();

}