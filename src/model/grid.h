#pragma once

#include <vector>
#include <string>
#include "snake.h"
#include <set>

using std::string, std::vector;

class Grid
{
private:
    int grid_size_x;
    int grid_size_y;
    vector<string> *level;
    vector<string> *grid;

public:
    std::set<std::pair<int, int>> *occupiedSpacesWall;
    std::set<std::pair<int, int>> *occupiedSpacesSnake;
    Grid();
    ~Grid();
    void setGrid(vector<string> *grid) { this->grid = grid; }
    void setLevel(vector<string> *level) { this->level = level; }
    vector<string> *getGrid() { return grid; }
    vector<string> *getLevel() { return level; }
    int getGridSizeX();
    int getGridSizeY();
    void reset();
};
