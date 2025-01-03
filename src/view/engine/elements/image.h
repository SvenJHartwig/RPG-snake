#pragma once

#include "element.h"
#include <vector>

namespace SEngine
{

    class Image : public Element
    {
    private:
        unsigned int texture;

    public:
        Image(int pos_x_top_left,
              int pos_y_top_left,
              int pos_x_bottom_right,
              int pos_y_bottom_right,
              std::string path);
        RenderData *createRenderData();
    };
}