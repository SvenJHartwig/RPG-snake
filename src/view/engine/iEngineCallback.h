#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SEngine
{
    // Callback for user input. Extend this class to receive user interaction.
    class IEngineCallback
    {
    public:
        virtual void reactOnInput(int input) = 0;
        virtual void setWindowClosed(bool closed) = 0;
    };
}