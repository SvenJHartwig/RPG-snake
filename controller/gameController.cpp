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
        // Get input
        //  char input;
        // input = std::cin.get();
        // reactOnInput(input);
        // gridController.moveSnakeRight();
        // Update game state
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
        char **chars = gridController.updateGrid(&grid);
        // Render output
        //  view->showGrid(chars, grid.getGridSizeY());
        cli.showGrid(chars, grid.getGridSizeX(), grid.getGridSizeY());
        usleep(1000000);
    }
}

Grid GameController::getGrid()
{
    return grid;
}

void GameController::setWindowClosed(bool closed)
{
    windowClosed = closed;
}