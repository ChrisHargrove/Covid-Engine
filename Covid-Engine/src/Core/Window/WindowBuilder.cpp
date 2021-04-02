#include "WindowBuilder.h"

#include "Window.h"

namespace Covid
{
    WindowBuilder::WindowBuilder() :
        m_width(800),
        m_height(600),
        m_title("New Window"),
        m_isFullScreen(false),
        m_isDecorated(true)
    {

    }

    WindowBuilder::~WindowBuilder()
    {

    }

    WindowBuilder& WindowBuilder::SetWidth(int width)
    {
        m_width = width;
        return *this;
    }

    WindowBuilder& WindowBuilder::SetHeight(int height)
    {
        m_height = height;
        return *this;
    }

    WindowBuilder& WindowBuilder::SetTitle(std::string title)
    {
        m_title = title;
        return *this;
    }

    WindowBuilder& WindowBuilder::SetFullScreen(bool isFullScreen)
    {
        m_isFullScreen = isFullScreen;
        return *this;
    }

    WindowBuilder& WindowBuilder::SetResizable(bool isResizable)
    {
        m_isResizeable = isResizable;
        return *this;;
    }

    WindowBuilder& WindowBuilder::SetDecorated(bool isDecorated)
    {
        m_isDecorated = isDecorated;
        return *this;
    }

    Window* WindowBuilder::Build()
    {
        glfwWindowHint(GLFW_RESIZABLE, m_isResizeable);
        glfwWindowHint(GLFW_DECORATED, m_isDecorated);

        m_window = new Window();
        if (m_isFullScreen)
        {
            m_window->window = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), nullptr);
        }
        else
        {
            m_window->window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        }

        if (!m_window->window)
        {
            Logger::EngineError("Window Creation Failed!");
            delete m_window;
            return nullptr;
        }
        return m_window;
    }
}