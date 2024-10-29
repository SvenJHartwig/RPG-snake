#include "grid.h"

Grid::Grid()
{
    grid_size_x = 20;
    grid_size_y = 20;
    level = new vector<string>();
    grid = new vector<string>();
}

Grid::~Grid()
{
}
int Grid::getGridSizeX()
{
    return this->grid_size_x;
}
int Grid::getGridSizeY()
{
    return this->grid_size_y;
}
