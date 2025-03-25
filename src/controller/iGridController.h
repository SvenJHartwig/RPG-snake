#pragma once

#include <string>
#include "../model/iSnake.h"
#include "../model/iGrid.h"

class IGridController
{
public:
    virtual void loadLevel(std::string path) = 0;
    virtual ISnake *getSnake() = 0;
    virtual IGrid *getGrid() = 0;
    virtual void showText(std::string text) = 0;
};