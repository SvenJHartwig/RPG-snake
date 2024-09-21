#pragma once

#include "../controller/iGameController.h"

class IGameView
{
public:
    virtual void setGameController(IGameController *gc) = 0;
    virtual int init() = 0;
    virtual void showGrid(char **grid, int grid_size_x, int grid_size_y) = 0;
    virtual ~IGameView() {};
};