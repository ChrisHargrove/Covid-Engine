#pragma once

#include "Window/Window.h"

namespace Covid
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void Init() = 0;

        virtual void Run() = 0;

        virtual void Shutdown() = 0;

    protected:
        Window* window;
    };

    //To be defined by the user.
    Application* CreateApplication();

}