#pragma once

#include "winCondition.h"

class IGrid
{
public:
    virtual void setGridSizeX(int grid_size_x) = 0;
    virtual void setGridSizeY(int grid_size_y) = 0;
    virtual int getGridSizeX() = 0;
    virtual int getGridSizeY() = 0;
    virtual void reset() = 0;
    virtual void setWinCondition(WinCondition winCondition) = 0;
    virtual WinCondition getWinCondition() = 0;
    virtual void saveToFile(const std::string &filename) = 0;
    virtual void loadFromFile(const std::string &filename) = 0;
};