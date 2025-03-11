#pragma once

#include "element.h"
#include "../iEngineCallback.h"

namespace SEngine
{
    class TextInput : public Element
    {
    private:
        bool focussed;

    public:
        std::string text;
        TextInput(int pos_x_top_left,
                  int pos_y_top_left,
                  int pos_x_bottom_right,
                  int pos_y_bottom_right);
        ~TextInput();
        RenderData *createRenderData() override;
        void click(IEngineCallback *callback) override;
        void reactOnInput(int input) override;
        void setWindowClosed(bool closed) override;
    };
}