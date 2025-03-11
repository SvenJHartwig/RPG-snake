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
        std::vector<std::vector<Sprite> *> *grid = NULL;
        unsigned int textureMap = 0;
        // Designates the fraction of the texture map a single sprite takes.
        // Must be between 0f and 1.0f
        float spriteFraction = 0;
        void initValues(int pos_x_top_left,
                        int pos_y_top_left,
                        int pos_x_bottom_right,
                        int pos_y_bottom_right);
        void initValues(int pos_x_top_left,
                        int pos_y_top_left,
                        int pos_x_bottom_right,
                        int pos_y_bottom_right,
                        const std::string &textureMapPath,
                        float spriteFraction);
        int focussedSpriteX;
        int focussedSpriteY;
        bool highlightFocussedSprite;

    public:
        SpriteGrid(int pos_x_top_left,
                   int pos_y_top_left,
                   int pos_x_bottom_right,
                   int pos_y_bottom_right);
        SpriteGrid(int pos_x_top_left,
                   int pos_y_top_left,
                   int pos_x_bottom_right,
                   int pos_y_bottom_right,
                   const std::string &textureMapPath,
                   float spriteFraction);
        int getFocussedSpriteX();
        int getFocussedSpriteY();
        void setHighlightFocussedSprite(bool highlight);
        bool getHighlightFocussedSprite();
        void click(IEngineCallback *callback, int x, int y) override;
        void reactOnInput(int input) override;
        void setWindowClosed(bool closed) override;
        RenderData *createRenderData() override;
        void setGrid(std::vector<std::vector<Sprite> *> *grid);
        std::vector<std::vector<Sprite> *> *getGrid();
    };
}