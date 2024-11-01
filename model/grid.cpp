#include "grid.h"

Grid::Grid()
{
    grid_size_x = 20;
    grid_size_y = 20;
    level = new vector<string>();
    // Initialize standard level
    for (int i = 0; i < grid_size_y; i++)
    {
        string temp(grid_size_y, 'x');
        level->push_back(temp);
        for (int j = 0; j < grid_size_x; j++)
        {
            if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
            {
                // Wall
                level->at(i)[j] = 'W';
            }
        }
    }
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
