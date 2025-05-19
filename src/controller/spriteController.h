#pragma once

#include <vector>
#include "../view/engine/elements/spriteGrid.h"
#include "../model/grid.h"
#include "../model/snake.h"

class SpriteController
{
public:
    static std::vector<std::vector<SEngine::Sprite> *> *getSpriteVector(Grid *grid, Snake *snake, std::vector<Food *> *food);
};