#pragma once

namespace Covid
{
    class Input;
    class Window;
    enum class CursorMode;

    class InputBuilder
    {
    public:

        InputBuilder();

        ~InputBuilder();

        InputBuilder& SetWindow(Window* window);

        InputBuilder& SetCursorMode(CursorMode cursorMode);

        Input* Build();

    private:
        Input* m_input;
        Window* m_window;

        CursorMode m_cursorMode;


    };
}


