#pragma once

#include <vector>
#include <string>
#include "snake.h"

using std::string, std::vector;

class Grid
{
private:
    int grid_size_x;
    int grid_size_y;
    vector<string> *grid;

public:
    Grid();
    ~Grid();
    void setGrid(vector<string> *grid);
    vector<string> *getGrid();
    int getGridSizeX();
    int getGridSizeY();
};
