#pragma once

#include <vector>
#include <string>
#include <set>

class GridElement
{
protected:
    int pos_x;
    int pos_y;

public:
    int getPosX();
    int getPosY();
    void setPosX(int pos);
    void setPosY(int pos);
};

class Grid
{
private:
    int grid_size_x;
    int grid_size_y;
    std::vector<std::string> *level;

public:
    std::set<std::pair<int, int>> *occupiedSpacesWall;
    std::set<std::pair<int, int>> *occupiedSpacesSnake;
    Grid();
    ~Grid();
    void setLevel(std::vector<std::string> *level) { this->level = level; }
    std::vector<std::string> *getLevel() { return level; }
    int getGridSizeX();
    int getGridSizeY();
    void reset();
};
