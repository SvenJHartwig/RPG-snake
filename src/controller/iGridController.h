#pragma once

#include <string>
#include "../model/iSnake.h"

class IGridController
{
public:
    virtual void loadLevel(std::string path) = 0;
    virtual ISnake *getSnake() = 0;
};