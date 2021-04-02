#include <Covid.h>

using namespace Covid;

class Quarantine: public Covid::Application
{
public:
    Quarantine() 
    {
    }

    ~Quarantine()
    {
    }

    virtual void Init()
    {
        Window::Init();
        window = Window::Create()
            .SetWidth(800)
            .SetHeight(600)
            .SetTitle("Fluent Window")
            .Build();

    }

    virtual void Run()
    {
        Init();

        while (!Window::ShouldClose(window))
        {
            glfwPollEvents();
        }

        Shutdown();
    }

    virtual void Shutdown()
    {

        delete window;
        Window::Shutdown();
    }

};

//Defines that we are going to use this application as our entry point.
ENTRY_POINT(Quarantine);