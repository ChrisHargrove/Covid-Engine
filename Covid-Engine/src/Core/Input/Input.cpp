#include "Input.h"

namespace Covid 
{
    Input::Input() :
        m_window(nullptr)
    {
    }

    Input::~Input()
    {
    }

#pragma region Static Methods

    InputBuilder Input::Create()
    {
        return InputBuilder();
    }

    void Input::OnKeyEventInternal(GLFWwindow* window, int keycode, int scancode, int action, int modifiers)
    {
        ((Input*)glfwGetWindowUserPointer(window))->m_keys[keycode]
            .SetKeyCode(keycode)
            .SetScanCode(scancode)
            .SetAction(action)
            .SetModifiers(modifiers);
        ((Input*)glfwGetWindowUserPointer(window))->OnKeyEvent.Invoke(KeyEvent(((Input*)glfwGetWindowUserPointer(window))->m_keys[keycode]));
    }

    void Input::OnMouseButtonEventInternal(GLFWwindow* window, int button, int action, int modifiers)
    {
        ((Input*)glfwGetWindowUserPointer(window))->m_buttons[button]
            .SetButton(button)
            .SetAction(action)
            .SetModifiers(modifiers);
        ((Input*)glfwGetWindowUserPointer(window))->OnMouseButtonEvent.Invoke(MouseButtonEvent(((Input*)glfwGetWindowUserPointer(window))->m_buttons[button]));
    }

    void Input::OnScrollEventInternal(GLFWwindow* window, double xOffset, double yOffset)
    {
        ((Input*)glfwGetWindowUserPointer(window))->m_scrollEvent
            .SetXOffset(xOffset)
            .SetYOffset(yOffset);
        ((Input*)glfwGetWindowUserPointer(window))->OnMouseScroll.Invoke(MouseScrollEvent(((Input*)glfwGetWindowUserPointer(window))->m_scrollEvent));
    }

    void Input::OnMouseMoveEventInternal(GLFWwindow* window, double xPos, double yPos)
    {
        ((Input*)glfwGetWindowUserPointer(window))->m_moveEvent
            .SetXDelta(xPos)
            .SetYDelta(yPos)
            .SetXPosition(xPos)
            .SetYPosition(yPos);
        ((Input*)glfwGetWindowUserPointer(window))->OnMouseMove.Invoke(MouseMoveEvent(((Input*)glfwGetWindowUserPointer(window))->m_moveEvent));
    }

#pragma endregion

    void Input::Poll()
    {
        m_keys.clear();
        m_buttons.clear();
        glfwPollEvents();
    }

    bool Input::GetKey(KeyCode keyCode)
    {
        KeyEvent currentEvent = m_keys[(int)keyCode];
        return currentEvent.GetAction() == GLFW_PRESS || currentEvent.GetAction() == GLFW_REPEAT;
    }

    bool Input::GetKeyUp(KeyCode keyCode)
    {
        return m_keys[(int)keyCode].GetAction() == GLFW_RELEASE;
    }

    bool Input::GetKeyDown(KeyCode keyCode)
    {
        return m_keys[(int)keyCode].GetAction() == GLFW_PRESS;
    }

    bool Input::GetButton(ButtonCode button)
    {
        MouseButtonEvent currentEvent = m_buttons[(int)button];
        return currentEvent.GetAction() == GLFW_PRESS || currentEvent.GetAction() == GLFW_REPEAT;
    }

    bool Input::GetButtonUp(ButtonCode button)
    {
        return m_buttons[(int)button].GetAction() == GLFW_RELEASE;
    }

    bool Input::GetButtonDown(ButtonCode button)
    {
        return m_buttons[(int)button].GetAction() == GLFW_PRESS;
    }

    double Input::GetMouseXPosition()
    {
        return m_moveEvent.GetXPosition();
    }

    double Input::GetMouseYPosition()
    {
        return m_moveEvent.GetYPosition();
    }

    std::pair<double, double> Input::GetMousePosition()
    {
        return std::pair<double, double>(m_moveEvent.GetXPosition(), m_moveEvent.GetYPosition());
    }

    double Input::GetMouseXDelta()
    {
        return m_moveEvent.GetXDelta();
    }

    double Input::GetMouseYDelta()
    {
        return m_moveEvent.GetYDelta();
    }

    std::pair<double, double> Input::GetMouseDelta()
    {
        return std::pair<double, double>(m_moveEvent.GetXDelta(), m_moveEvent.GetYDelta());
    }

    Input& Input::SetCursorMode(CursorMode cursorMode)
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, (int)cursorMode);
        return *this;
    }

}
