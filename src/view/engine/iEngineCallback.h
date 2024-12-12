#pragma once

namespace SEngine
{
    class IEngineCallback
    {
    public:
        virtual void reactOnInput(char input) = 0;
        virtual void setWindowClosed(bool closed) = 0;
    };
}