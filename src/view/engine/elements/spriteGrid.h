#pragma once

#include "element.h"
#include <vector>

namespace SEngine
{
    class Sprite
    {
    public:
        float texBaseX, texBaseY;
    };

    class SpriteGrid : public Element
    {
    private:
        std::vector<std::vector<Sprite> *> *grid;
        unsigned int textureMap;
        // Designates the fraction of the texture map a single sprite takes.
        // Must be between 0f and 1.0f
        float spriteFraction;

    public:
        SpriteGrid(int pos_x_top_left,
                   int pos_y_top_left,
                   int pos_x_bottom_right,
                   int pos_y_bottom_right,
                   std::string path,
                   float spriteFraction);
        RenderData *createRenderData();
        void setGrid(std::vector<std::vector<Sprite> *> *grid) { this->grid = grid; }
        std::vector<std::vector<Sprite> *> *getGrid() { return grid; }
    };
}