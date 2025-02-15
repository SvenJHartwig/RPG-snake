#pragma once

#include <vector>
#include <string>
#include <set>
#include "winCondition.h"
#include <iostream>
#include <fstream>
#include "gridElement.h"
#include "mob.h"
#include "teleporter.h"

// Holds data for a level as a vector of strings, likely to be changed to a more flexible
// structure in the future.
class Grid
{
private:
    int grid_size_x;
    int grid_size_y;
    std::vector<std::vector<GridElement *> *> *level;
    WinCondition winCon = WinCondition(NONE, 0);
    std::vector<Mob *> *mobs;

public:
    std::set<std::pair<int, int>> *occupiedSpacesWall;
    std::set<std::pair<int, int>> *occupiedSpacesSnake;
    // Create a grid and initialize the standard level
    Grid();
    ~Grid();
    void setLevel(std::vector<std::vector<GridElement *> *> *level) { this->level = level; }
    std::vector<std::vector<GridElement *> *> *getLevel() { return level; }
    void setGridSizeX(int grid_size_x) { this->grid_size_x = grid_size_x; }
    void setGridSizeY(int grid_size_y) { this->grid_size_y = grid_size_y; }
    int getGridSizeX();
    int getGridSizeY();
    void reset();
    void setWinCondition(WinCondition winCondition) { this->winCon = winCondition; }
    WinCondition getWinCondition() { return winCon; }
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);
    std::vector<Mob *> *getMobs();
};
