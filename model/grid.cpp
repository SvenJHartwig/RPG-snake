#include "grid.h"

Grid::Grid()
{
    grid_size_x = 20;
    grid_size_y = 20;
    grid = new vector<string>();
}

Grid::~Grid()
{
}

void Grid::setGrid(vector<string> *grid)
{
    this->grid = grid;
}

vector<string> *Grid::getGrid()
{
    return grid;
}

int Grid::getGridSizeX()
{
    return this->grid_size_x;
}
int Grid::getGridSizeY()
{
    return this->grid_size_y;
}
