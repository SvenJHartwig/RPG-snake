#pragma once

#include <vector>
#include <string>
#include "snake.h"
#include <set>

class GridElement
{
};

class Grid
{
private:
    int grid_size_x;
    int grid_size_y;
    std::vector<std::string> *level;
    std::vector<std::string> *grid;

public:
    std::set<std::pair<int, int>> *occupiedSpacesWall;
    std::set<std::pair<int, int>> *occupiedSpacesSnake;
    Grid();
    ~Grid();
    void setGrid(std::vector<std::string> *grid) { this->grid = grid; }
    void setLevel(std::vector<std::string> *level) { this->level = level; }
    std::vector<std::string> *getGrid() { return grid; }
    std::vector<std::string> *getLevel() { return level; }
    int getGridSizeX();
    int getGridSizeY();
    void reset();
};
