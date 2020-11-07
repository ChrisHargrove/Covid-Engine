#pragma once

#include "Application.h"

/* ----------------------------------------------------------------------------
    Application Creation Macro
    This is to be used inside the clients application to specify
    the entry point for the program so that the game engine will
    run.
---------------------------------------------------------------------------- */
#define ENTRY_POINT(T) Covid::Application* Covid::CreateApplication() { return new T(); }

/* ----------------------------------------------------------------------------
    Extern CreateApplication Declaration
    This defines that the CreateApplication function will be defined outside of
    this compilation unit.
---------------------------------------------------------------------------- */
extern Covid::Application* Covid::CreateApplication();

/* ----------------------------------------------------------------------------
    Program Entry Point
    This is where the program actually starts from but is abstracted away from
    the end user so they dont have to deal with it.
---------------------------------------------------------------------------- */
int main(int argc, char** argv)
{
    auto app = Covid::CreateApplication();
    app->Run();
    delete app;

    return 0;
}