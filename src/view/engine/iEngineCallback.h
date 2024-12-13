#pragma once

namespace SEngine
{
    // Callback for user input. Extend this class to receive user interaction.
    class IEngineCallback
    {
    public:
        virtual void reactOnInput(char input) = 0;
        virtual void setWindowClosed(bool closed) = 0;
    };
}