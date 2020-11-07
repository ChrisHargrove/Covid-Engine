#pragma once

namespace Covid
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    //To be defined by the user.
    Application* CreateApplication();

}