#pragma once

#include "KeyCodes.h"
#include "ButtonCodes.h"

namespace Covid
{
    struct KeyEvent
    {
    public:
        KeyEvent() :
            m_keycode(-1),
            m_scancode(-1),
            m_action(-1),
            m_modifiers(-1)
        {
        }

        KeyEvent& SetKeyCode(int keycode)
        {
            m_keycode = keycode;
            return *this;
        }

        KeyEvent& SetScanCode(int scancode)
        {
            m_scancode = scancode;
            return *this;
        }

        KeyEvent& SetAction(int action)
        {
            m_action = action;
            return *this;
        }

        KeyEvent& SetModifiers(int modifiers)
        {
            m_modifiers = modifiers;
            return *this;
        }

        KeyCode GetKeyCode()
        {
            return (KeyCode)m_keycode;
        }

        int GetScanCode()
        {
            return m_scancode;
        }

        int GetAction()
        {
            return m_action;
        }

        int GetModifiers()
        {
            return m_modifiers;
        }

    private:
        int m_keycode;
        int m_scancode;
        int m_action;
        int m_modifiers;
    };

    class MouseButtonEvent
    {
    public:
        MouseButtonEvent() :
            m_button(-1),
            m_action(-1),
            m_modifiers(-1)
        {
        }

        MouseButtonEvent& SetButton(int button)
        {
            m_button = button;
            return *this;
        }

        MouseButtonEvent& SetAction(int action)
        {
            m_action = action;
            return *this;
        }

        MouseButtonEvent& SetModifiers(int modifiers)
        {
            m_modifiers = modifiers;
            return *this;
        }

        ButtonCode GetButton()
        {
            return (ButtonCode)m_button;
        }

        int GetAction()
        {
            return m_action;
        }

        int GetModifiers()
        {
            return m_modifiers;
        }

    private:
        int m_button;
        int m_action;
        int m_modifiers;
    };

    class MouseScrollEvent
    {
    public:
        MouseScrollEvent() :
            m_xOffset(0),
            m_yOffset(0)
        {
        }

        MouseScrollEvent& SetXOffset(double xOffset)
        {
            m_xOffset = xOffset;
            return *this;
        }

        MouseScrollEvent& SetYOffset(double yOffset)
        {
            m_yOffset = yOffset;
            return *this;
        }

        double GetXOffset()
        {
            return m_xOffset;
        }

        double GetYOffset()
        {
            return m_yOffset;
        }

    private:
        double m_xOffset;
        double m_yOffset;
    };

    class MouseMoveEvent
    {
    public:
        MouseMoveEvent() :
            m_xPosition(0),
            m_yPosition(0),
            m_deltaX(0),
            m_deltaY(0)
        {
        }

        MouseMoveEvent& SetXPosition(double xPosition)
        {
            m_xPosition = xPosition;
            return *this;
        }

        MouseMoveEvent& SetYPosition(double yPosition)
        {
            m_yPosition = yPosition;
            return *this;
        }

        MouseMoveEvent& SetXDelta(double xPosition)
        {
            m_deltaX = xPosition - m_xPosition;
            return *this;
        }

        MouseMoveEvent& SetYDelta(double yPosition)
        {
            m_deltaY = yPosition - m_yPosition;
            return *this;
        }

        double GetXPosition()
        {
            return m_xPosition;
        }

        double GetYPosition()
        {
            return m_yPosition;
        }

        double GetXDelta()
        {
            return m_deltaX;
        }

        double GetYDelta()
        {
            return m_deltaY;
        }

    private:
        double m_xPosition;
        double m_yPosition;

        double m_deltaX;
        double m_deltaY;
    };
}