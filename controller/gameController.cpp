#include "gameController.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include "../view/cliView.h"

void gameControllerInitView(IGameView *view)
{
    view->init();
}

void GameController::setView(IGameView *view)
{
    this->view = view;
}

void GameController::reactOnInput(char input)
{
    lastInput = input;
}

void GameController::mainLoop()
{
    view->setGameController(this);
    std::thread t1(gameControllerInitView, view);
    CliView cli;
    while (!gridController.isGameOver() && !windowClosed)
    {
        switch (lastInput)
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
        // Updates the grid in memory to be read by the graphics engine
        char **chars = gridController.updateGrid();
        // Print the grid to console for debug purposes
        cli.showGrid(chars, grid.getGridSizeX(), grid.getGridSizeY());
        usleep(speed);
    }
}

Grid GameController::getGrid()
{
    return *gridController.getGrid();
}

void GameController::setWindowClosed(bool closed)
{
    windowClosed = closed;
}