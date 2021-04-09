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

        float elapsedTime = 0;

        while (!Window::ShouldClose(m_window))
        {
            elapsedTime += m_time->GetDeltaTime();

            m_input->Poll();

            Update();
            if(elapsedTime >= 1.0f / 60.0f)
            {
                elapsedTime -= 1.0f / 60.0f;
                FixedUpdate();
            }
            m_time->Update();
        }

        Shutdown();
    }
}