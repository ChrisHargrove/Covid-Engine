#include "InputBuilder.h"

#include "Input.h"
#include "../Window/Window.h"

namespace Covid
{
    InputBuilder::InputBuilder() :
        m_input(nullptr),
        m_cursorMode(CursorMode::Normal)
    {
    }

    InputBuilder::~InputBuilder()
    {
    }

    InputBuilder& InputBuilder::SetWindow(Window* window)
    {
        m_window = window;
        return *this;
    }

    InputBuilder& InputBuilder::SetCursorMode(CursorMode cursorMode)
    {
        m_cursorMode = cursorMode;
        return *this;
    }


    Input* InputBuilder::Build()
    {
        m_input = new Input();
        m_input->m_window = m_window->m_window;

        glfwSetInputMode(m_input->m_window, GLFW_CURSOR, (int)m_cursorMode);

        glfwSetKeyCallback(m_input->m_window, Input::OnKeyEventInternal);
        glfwSetMouseButtonCallback(m_input->m_window, Input::OnMouseButtonEventInternal);
        glfwSetCursorPosCallback(m_input->m_window, Input::OnMouseMoveEventInternal);
        glfwSetScrollCallback(m_input->m_window, Input::OnScrollEventInternal);

        glfwSetWindowUserPointer(m_input->m_window, m_input);
        return m_input;
    }
}