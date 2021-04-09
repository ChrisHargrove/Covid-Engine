#include "Window.h"

namespace Covid
{
    Window::Window() :
        m_window(nullptr)
    {
    }

    Window::~Window()
    {
        if (m_window) glfwDestroyWindow(m_window);
    }

#pragma region Static Methods

    void Window::Init()
    {
        if (!glfwInit())
        {
            Logger::EngineError("GLFW Initialization Failed: {}", glfwGetError(NULL));
            return;
        }
        glfwSetErrorCallback(Window::OnError);
        Logger::EngineInfo("GLFW Initialization Successful!");
    }

    void Window::Shutdown()
    {
        Logger::EngineInfo("Terminating GLFW!");
        glfwTerminate();
    }

    WindowBuilder Window::Create()
    {
        return WindowBuilder();
    }

    bool Window::ShouldClose(Window* instance)
    {
        if (instance)
        {
            return glfwWindowShouldClose(instance->m_window);
        }
        else
        {
            Logger::EngineWarn("Window instance was null!");
            return false;
        }
    }

    void Window::OnError(int errorCode, const char* description)
    {
        Logger::EngineError("GLFW: \nError Code: {} \nError Description: {}", errorCode, description);
    }

#pragma endregion

    void Window::SetSize(int width, int height)
    {
        glfwSetWindowSize(m_window, width, height);
    }

    void Window::GetSize(int* width, int* height)
    {
        glfwGetWindowSize(m_window, width, height);
    }


}