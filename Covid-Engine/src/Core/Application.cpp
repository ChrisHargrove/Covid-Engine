#include "Application.h"

#include "Input/Input.h"

namespace Covid
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        Init();

        while (!Window::ShouldClose(m_window))
        {
            m_input->Poll();

            Update();


            m_time->Update();
        }

        Shutdown();
    }
}