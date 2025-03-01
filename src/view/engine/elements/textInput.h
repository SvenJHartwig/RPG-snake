#pragma once

#include "element.h"
#include "../iEngineCallback.h"

namespace SEngine
{
    class TextInput : public Element, public IEngineCallback
    {
    private:
        std::string text;
        bool focussed;

    public:
        TextInput(int pos_x_top_left,
                  int pos_y_top_left,
                  int pos_x_bottom_right,
                  int pos_y_bottom_right);
        ~TextInput();
        RenderData *createRenderData() override;
        void reactOnInput(int input) override;
        void setWindowClosed(bool closed) override;
    };
}