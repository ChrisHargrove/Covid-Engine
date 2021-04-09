#pragma once

#include "GLFW/glfw3.h"

#include "../Logger.h"
#include "InputBuilder.h"
#include "InputEvents.h"
#include "KeyCodes.h"
#include "ButtonCodes.h"

#include "../../Utilities/Action.h"

namespace Covid
{
    enum class CursorMode
    {
        Normal = GLFW_CURSOR_NORMAL,
        Hidden = GLFW_CURSOR_HIDDEN,
        Disabled = GLFW_CURSOR_DISABLED
    };

    class Input
    {
        friend InputBuilder;

    private:
        Input();

        static void OnKeyEventInternal(GLFWwindow* window, int keycode, int scancode, int action, int modifiers);

        static void OnMouseButtonEventInternal(GLFWwindow* window, int button, int action, int modifiers);

        static void OnScrollEventInternal(GLFWwindow* window, double xOffset, double yOffset);

        static void OnMouseMoveEventInternal(GLFWwindow* window, double xPos, double xOffset);

    public:
        ~Input();   

        void Poll();

        bool GetKey(KeyCode keyCode);
        bool GetKeyUp(KeyCode keyCode);
        bool GetKeyDown(KeyCode keyCode);

        bool GetButton(ButtonCode button);
        bool GetButtonUp(ButtonCode button);
        bool GetButtonDown(ButtonCode button);

        double GetMouseXPosition();
        double GetMouseYPosition();
        std::pair<double, double> GetMousePosition();
        double GetMouseXDelta();
        double GetMouseYDelta();
        std::pair<double, double> GetMouseDelta();

        static InputBuilder Create();

        Input& SetCursorMode(CursorMode cursorMode);

    public:
        Action<KeyEvent> OnKeyEvent;
        Action<MouseButtonEvent> OnMouseButtonEvent;
        Action<MouseMoveEvent> OnMouseMove;
        Action<MouseScrollEvent> OnMouseScroll;

    private:
        GLFWwindow* m_window;

        MouseScrollEvent m_scrollEvent;
        MouseMoveEvent m_moveEvent;

        std::unordered_map<int, KeyEvent> m_keys;
        std::unordered_map<int, MouseButtonEvent> m_buttons;



    };
}