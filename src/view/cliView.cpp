#include "cliView.h"
#include <iostream>
#include <stdlib.h>

void CliView::setGameController(IGameController *gc)
{
}

int CliView::init()
{
    return 0;
}

void CliView::showGrid(char **grid, int grid_size_x, int grid_size_y)
{
    // Warning: This call is OS specific
    system("clear");
    for (int i = 0; i < grid_size_y; i++)
    {
        std::cout << grid[i] << std::endl;
    }
}