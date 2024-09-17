#include "gameController.h"
#include <unistd.h>
#include <iostream>

void GameController::reactOnInput(char input)
{
    switch (input)
    {
    case 'd':
        gridController.moveSnakeRight();
        break;
    case 'w':
        gridController.moveSnakeUp();
        break;
    case 'a':
        gridController.moveSnakeLeft();
        break;
    case 's':
        gridController.moveSnakeDown();
        break;

    default:
        break;
    }
}

void GameController::mainLoop()
{
    while (!gridController.isGameOver())
    {
        // Get input
        char input;
        input = std::cin.get();
        reactOnInput(input);
        // gridController.moveSnakeRight();
        // Update game state
        char **chars = gridController.updateGrid(&grid);
        // Render output
        view.showGrid(chars, grid.getGridSizeY());
        usleep(1000000);
    }
}