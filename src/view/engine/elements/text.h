#pragma once

#include "element.h"

namespace SEngine
{
    class Text : public Element
    {
    public:
        std::string text;
        Text(int pos_x_top_left,
             int pos_y_top_left,
             int pos_x_bottom_right,
             int pos_y_bottom_right);
        ~Text();
        void click(IEngineCallback *callback, int x, int y) override;
        void reactOnInput(int input) override;
        void setWindowClosed(bool closed) override;
        RenderData *createRenderData() override;
    };
}