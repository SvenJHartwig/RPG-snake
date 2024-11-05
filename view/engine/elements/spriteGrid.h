#pragma once

#include "element.h"

class SpriteGrid : public Element
{
public:
    SpriteGrid(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right);
    void render();
};