#include <Covid.h>

//TEMP
#include "GLFW/glfw3.h"

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
        m_window = Window::Create()
            .SetWidth(800)
            .SetHeight(600)
            .SetTitle("Fluent Window")
            .Build();

        m_input = Input::Create()
            .SetWindow(m_window)
            .Build();

        m_time = new Time();

    }

    virtual void Update()
    {
        Logger::EngineTrace("Delta Time: {0:.20f}", m_time->GetDeltaTime());
    }

    virtual void FixedUpdate()
    {
    }

    virtual void Shutdown()
    {

        delete m_window;
        Window::Shutdown();
    }

};

//Defines that we are going to use this application as our entry point.
ENTRY_POINT(Quarantine);