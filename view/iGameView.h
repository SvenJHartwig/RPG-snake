#pragma once

class IGameView
{
public:
    virtual int init() = 0;
    virtual void showGrid(char **grid, int grid_size_y) = 0;
    virtual ~IGameView() {};
};