#pragma once

#include <string>

namespace Covid
{
    class Window;

    class WindowBuilder
    {
    public:
        WindowBuilder();

        ~WindowBuilder();

        WindowBuilder& SetWidth(int width);

        WindowBuilder& SetHeight(int height);

        WindowBuilder& SetTitle(std::string title);

        WindowBuilder& SetFullScreen(bool isFullScreen);

        WindowBuilder& SetResizable(bool isResizable);

        WindowBuilder& SetDecorated(bool isDecorated);

        Window* Build();

    private:
        Window* m_window;

        int m_width;
        int m_height;
        std::string m_title;

        bool m_isFullScreen;
        bool m_isResizeable;
        bool m_isDecorated;

    };
}


