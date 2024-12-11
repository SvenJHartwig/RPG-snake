#pragma once

#include <vector>
#include <string>
#include <set>

enum GridElementType
{
    GROUND,
    WALL,
    SNAKE,
    FOOD
};

class GridElement
{
protected:
    GridElementType gridElementType;
    int pos_x;
    int pos_y;

public:
    GridElementType getGridElementType();
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
    std::vector<std::vector<GridElement> *> *grid;

public:
    std::set<std::pair<int, int>> *occupiedSpacesWall;
    std::set<std::pair<int, int>> *occupiedSpacesSnake;
    Grid();
    ~Grid();
    void setGrid(std::vector<std::vector<GridElement> *> *grid) { this->grid = grid; }
    void setLevel(std::vector<std::string> *level) { this->level = level; }
    std::vector<std::vector<GridElement> *> *getGrid() { return grid; }
    std::vector<std::string> *getLevel() { return level; }
    int getGridSizeX();
    int getGridSizeY();
    void reset();
};
