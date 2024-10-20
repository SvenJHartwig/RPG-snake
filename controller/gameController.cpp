#include "gameController.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include "../view/cliView.h"

GameController::GameController()
{
    gridController = new GridController(this);
}

GameController::~GameController()
{
}

void gameControllerInitView(IGameView *view)
{
    view->init();
    view->showMainMenu();
    view->renderingLoop();
}

void GameController::setView(IGameView *view)
{
    this->view = view;
}

void GameController::reactOnInput(char input)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (input == 'p')
        {
            gameState = IN_GAME;
        }
    case IN_GAME:
        if (eatCount > 0 &&
            (lastDirection == 'a' && input == 'd' ||
             lastDirection == 'w' && input == 's' ||
             lastDirection == 'd' && input == 'a' ||
             lastDirection == 's' && input == 'w'))
        {
            return;
        }
        lastInput = input;
        break;
    default:
        break;
    }
}

void GameController::mainLoop()
{
    view->setGameController(this);
    new std::thread(gameControllerInitView, view);
    //  CliView cli;

    while (!gridController->isGameOver() && !windowClosed)
    {
        mainLoopIteration();
        // Print the grid to console for debug purposes
        //   cli.showGrid(chars, gridController->getGrid()->getGridSizeX(), gridController->getGrid()->getGridSizeY());
        usleep(speed);
    }
}

void GameController::mainLoopIteration()
{

    switch (lastInput)
    {
    case 'd':
        lastDirection = 'd';
        gridController->moveSnakeRight();
        break;
    case 'w':
        lastDirection = 'w';
        gridController->moveSnakeUp();
        break;
    case 'a':
        lastDirection = 'a';
        gridController->moveSnakeLeft();
        break;
    case 's':
        lastDirection = 's';
        gridController->moveSnakeDown();
        break;

    default:
        break;
    }
    // Updates the grid in memory to be read by the graphics engine
    char **chars = gridController->updateGrid();
}

Grid GameController::getGrid()
{
    return *gridController->getGrid();
}

void GameController::setWindowClosed(bool closed)
{
    windowClosed = closed;
}

GridController *GameController::getGridController()
{
    return gridController;
}

SpeedSetting GameController::getSpeed()
{
    return speed;
}

void GameController::eat(bool isSpecial)
{
    if (isSpecial)
        score += 2;
    else
        score++;
    eatCount++;
    if (eatCount == 2)
    {
        speed = l2;
    }
    else if (eatCount == 4)
    {
        speed = l3;
    }
    else if (eatCount == 6)
    {
        speed = l4;
    }
    else if (eatCount == 8)
    {
        speed = l5;
    }
    else if (eatCount == 10)
    {
        speed = l6;
    }
}

char GameController::getLastDirection()
{
    return lastDirection;
}

int GameController::getScore()
{
    return score;
}

GameState GameController::getGameState()
{
    return gameState;
}