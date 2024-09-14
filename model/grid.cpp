#include "grid.h"

Grid::Grid(){
    grid_size_x = 20;
    grid_size_y = 10;
    grid = new char *[grid_size_y];
}

Grid::~Grid(){
}

void Grid::setGrid(char **grid){
    this->grid = grid;
}

char **Grid::getGrid(){
    return grid;
}

int Grid::getGridSizeX(){
    return this->grid_size_x;
}
int Grid::getGridSizeY(){
    return this->grid_size_y;
}
