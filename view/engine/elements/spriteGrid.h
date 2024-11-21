#pragma once

#include "element.h"
#include <vector>
#include <string>

class SpriteGrid : public Element
{
private:
    std::vector<std::string> *grid;

public:
    SpriteGrid(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right);
    RenderData *createRenderData();
    void setGrid(std::vector<std::string> *grid) { this->grid = grid; }
    std::vector<std::string> *getGrid() { return grid; }
};