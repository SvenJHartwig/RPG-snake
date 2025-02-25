#pragma once

#include "element.h"

namespace SEngine
{
    class TextInput : public Element
    {
    public:
        TextInput(int pos_x_top_left,
                  int pos_y_top_left,
                  int pos_x_bottom_right,
                  int pos_y_bottom_right);
        ~TextInput();
        RenderData *createRenderData() override;
    };
}