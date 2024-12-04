#pragma once

#include "element.h"
#include "../TextRenderer/TextRenderer.h"

class Text : public Element
{
public:
    std::string text;
    Text(int pos_x_top_left,
         int pos_y_top_left,
         int pos_x_bottom_right,
         int pos_y_bottom_right);
    ~Text();
    RenderData *createRenderData();
};