#pragma once

#include "element.h"
#include <vector>

class Sprite
{
public:
    float texBaseX, texBaseY;
};

class SpriteGrid : public Element
{
private:
    std::vector<std::vector<Sprite> *> *grid;

public:
    SpriteGrid(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right);
    RenderData *createRenderData();
    void setGrid(std::vector<std::vector<Sprite> *> *grid) { this->grid = grid; }
    std::vector<std::vector<Sprite> *> *getGrid() { return grid; }
};