#include "grid.h"

using std::vector, std::string;

int GridElement::getPosX()
{
    return pos_x;
}

int GridElement::getPosY()
{
    return pos_y;
}
void GridElement::setPosX(int pos)
{
    this->pos_x = pos;
}
void GridElement::setPosY(int pos)
{
    this->pos_y = pos;
}

void Grid::reset()
{
    grid_size_x = 20;
    grid_size_y = 20;
    level = new vector<string>();
    occupiedSpacesWall = new std::set<std::pair<int, int>>();
    occupiedSpacesSnake = new std::set<std::pair<int, int>>();
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
                occupiedSpacesWall->insert({j, i});
            }
        }
    }
}
Grid::Grid()
{
    // Initialize standard level
    reset();
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
