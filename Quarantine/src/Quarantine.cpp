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

        m_input->OnKeyEvent.Subscribe("Test Key", [](Covid::KeyEvent evt) {
            if(evt.GetKeyCode() == KeyCode::E)
            {
                Logger::EngineDebug("Key Pressed Callback");
            }
        });

    }

    virtual void Run()
    {
        Init();

        while (!Window::ShouldClose(m_window))
        {
            m_input->Poll();


        }

        Shutdown();
    }

    virtual void Shutdown()
    {

        delete m_window;
        Window::Shutdown();
    }

};

//Defines that we are going to use this application as our entry point.
ENTRY_POINT(Quarantine);